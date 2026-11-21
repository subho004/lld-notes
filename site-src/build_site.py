#!/usr/bin/env python3
"""Generate the root index.html (a self-contained static site).

Usage (from anywhere):  python3 site-src/build_site.py

Reads every chapter folder (README, revision notes, Java/Python/C++ sources),
the notes/ folder and embeds everything as JSON inside template.html, so the
resulting index.html works from file:// or any static host. The protocol-explorer
folder is NOT embedded; it is linked as its own sub page.
"""
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
TEMPLATE = Path(__file__).resolve().parent / "template.html"
OUT = ROOT / "index.html"

# (folder, number, book chapter title, pattern label, one-line intent)
CHAPTERS = [
    ("chap1-strategy", 1, "Welcome to Design Patterns", "Strategy",
     "Define a family of algorithms, encapsulate each one and make them interchangeable."),
    ("chap2-observer", 2, "Keeping your Objects in the Know", "Observer",
     "When one object changes state, all its dependents are notified automatically."),
    ("chap3-decorator", 3, "Decorating Objects", "Decorator",
     "Attach extra responsibilities to an object dynamically, without subclassing."),
    ("chap4-factory", 4, "Baking with OO Goodness", "Factory Method · Abstract Factory",
     "Let subclasses decide what to create, or create whole families of related objects."),
    ("chap5-singleton", 5, "One-of-a-Kind Objects", "Singleton",
     "Ensure a class has one instance and give it a global access point."),
    ("chap6-command", 6, "Encapsulating Invocation", "Command",
     "Turn a request into an object so you can queue, log and undo it."),
    ("chap7-adaptive", 7, "Being Adaptive", "Adapter · Facade",
     "Convert one interface into another, or hide a subsystem behind a simple one."),
    ("chap8-template-method", 8, "Encapsulating Algorithms", "Template Method",
     "Fix an algorithm's skeleton in a base class and let subclasses fill in the steps."),
    ("chap9-iterator-composite", 9, "Well-Managed Collections", "Iterator · Composite",
     "Traverse any collection uniformly, and treat groups and leaves the same way."),
    ("chap10-state-pattern", 10, "The State of Things", "State",
     "Let an object change its behavior when its internal state changes."),
    ("chap11-proxy", 11, "Controlling Object Access", "Proxy",
     "Stand in for another object to control access: remote, virtual, protection."),
    ("chap12-compound", 12, "Patterns of Patterns", "Compound · MVC",
     "Combine several patterns into one design: the duck simulator and Model-View-Controller."),
    ("chap13-patterns-in-the-real-world", 13, "Patterns in the Real World", "Better living with patterns",
     "What a pattern is, how patterns are categorized and found, and what anti-patterns are."),
    ("chap14-leftover-patterns", 14, "Appendix: Leftover Patterns", "The other GoF patterns",
     "Bridge, Builder, Chain of Responsibility, Flyweight, Interpreter, Mediator, Memento, Prototype, Visitor."),
]

LANGS = {
    "java": {".java"},
    "python": {".py"},
    "cpp": {".cpp", ".h", ".hpp", ".cc"},
}
EXTRA_NAMES = {"cpp": {"Makefile"}, "python": set(), "java": set()}
EXTRA_EXT_ALL = {".txt"}  # data files such as test.txt


def read(p: Path) -> str:
    return p.read_text(encoding="utf-8", errors="replace")


def collect_code(chapter_dir: Path):
    out = {}
    for lang, exts in LANGS.items():
        base = chapter_dir / lang
        files = []
        if base.is_dir():
            for f in sorted(base.rglob("*"), key=lambda x: str(x).lower()):
                if not f.is_file() or any(part in {"build", "__pycache__"} for part in f.parts):
                    continue
                if f.suffix in exts or f.name in EXTRA_NAMES[lang] or f.suffix in EXTRA_EXT_ALL:
                    files.append({"n": f.relative_to(base).as_posix(), "c": read(f)})
        out[lang] = files
    return out


def build_chapters():
    chapters = []
    for folder, num, title, pattern, tagline in CHAPTERS:
        d = ROOT / folder
        notes_p = d / f"{folder}-notes.md"
        readme_p = d / "README.md"
        chapters.append({
            "id": folder,
            "num": num,
            "title": title,
            "pattern": pattern,
            "tagline": tagline,
            "notes": read(notes_p) if notes_p.exists() else None,
            "readme": read(readme_p) if readme_p.exists() else None,
            "files": collect_code(d),
        })
    return chapters


# (file name, id, title, group, kind)
GUIDES = [
    ("java-interview-questions-answers.md", "java-qa", "Java interview Q&A", "Interview prep", "md"),
    ("python-interview-questions-answers.md", "python-qa", "Python interview Q&A", "Interview prep", "md"),
    ("c++-interview-questions-answers.md", "cpp-qa", "C++ interview Q&A", "Interview prep", "md"),
    ("java interview questions.txt", "java-q", "Java question list", "Question lists", "txt"),
    ("python interview questions.txt", "python-q", "Python question list", "Question lists", "txt"),
    ("c++ interview questions.txt", "cpp-q", "C++ question list", "Question lists", "txt"),
    ("100+ Python challenging programming exercises for Python 3.md", "py-ex", "100+ Python exercises", "Practice", "md"),
    ("100+ python challenging programming exercises answers.md", "py-ex-ans", "Python exercises: answers", "Practice", "md"),
    ("100+ Python challenging programming exercises.txt", "py-ex-txt", "Python exercises (plain text)", "Practice", "txt"),
]


def build_guides():
    guides = []
    for fname, gid, title, group, kind in GUIDES:
        p = ROOT / "notes" / fname
        if p.exists():
            guides.append({"id": gid, "title": title, "group": group, "kind": kind, "file": f"notes/{fname}", "text": read(p)})
        else:
            print("warning: missing", p)
    return guides


SKIP_DIRS = {".git", "node_modules", "__pycache__", "build", ".claude", ".agents", ".idea", ".vscode"}
SKIP_FILES = {".DS_Store", "skills-lock.json"}
COLLAPSE = {
    "head_first_markdown": "book page files (not published on the site)",
    "protocol-explorer": "separate sub page (own index.html)",
}


def build_tree(chapters, guides):
    """Nested listing of the whole repo. File entries carry 'r' (site route) or 'h' (direct relative href)."""
    routes = {}
    for c in chapters:
        cid = c["id"]
        routes[f"{cid}/README.md"] = f"#/{cid}/readme"
        routes[f"{cid}/{cid}-notes.md"] = f"#/{cid}/notes"
        for lang, files in c["files"].items():
            for f in files:
                routes[f"{cid}/{lang}/{f['n']}"] = f"#/{cid}/code/{lang}/{f['n']}"
    for g in guides:
        pass
    guide_files = {fname: gid for fname, gid, *_ in GUIDES}
    for fname, gid in guide_files.items():
        routes[f"notes/{fname}"] = f"#/guide/{gid}"
    routes["Readme.md"] = "#/extras"

    def walk(d: Path):
        out = []
        for e in sorted(d.iterdir(), key=lambda x: (x.is_file(), x.name.lower())):
            if e.name in SKIP_DIRS or e.name in SKIP_FILES or e.name.endswith(".pyc"):
                continue
            rel = e.relative_to(ROOT).as_posix()
            if e.is_dir():
                if e.name in COLLAPSE and d == ROOT:
                    count = sum(1 for _ in e.rglob("*") if _.is_file())
                    node = {"n": e.name, "t": "d", "note": f"{count} files, {COLLAPSE[e.name]}", "k": []}
                    if e.name == "protocol-explorer":
                        node["h"] = "protocol-explorer/index.html"
                    out.append(node)
                else:
                    out.append({"n": e.name, "t": "d", "k": walk(e)})
            else:
                node = {"n": e.name, "t": "f", "s": e.stat().st_size}
                if rel in routes:
                    node["r"] = routes[rel]
                elif rel != "index.html":
                    node["h"] = rel
                out.append(node)
        return out

    return walk(ROOT)


def main():
    chapters = build_chapters()
    guides = build_guides()
    data = {
        "chapters": chapters,
        "guides": guides,
        "readme": read(ROOT / "Readme.md") if (ROOT / "Readme.md").exists() else "",
        "tree": build_tree(chapters, guides),
        "pdf": {"title": "OOP in C++ (PDF)", "href": "notes/OOP_C++.pdf"} if (ROOT / "notes/OOP_C++.pdf").exists() else None,
        "explorer": {"title": "Protocol Explorer", "href": "protocol-explorer/index.html"}
        if (ROOT / "protocol-explorer/index.html").exists() else None,
    }
    payload = json.dumps(data, ensure_ascii=False, separators=(",", ":"))
    # keep the JSON safe inside a <script> element
    payload = payload.replace("</", "<\\/").replace("<!--", "<\\!--")
    html = read(TEMPLATE)
    if "__DATA__" not in html:
        raise SystemExit("template.html is missing the __DATA__ placeholder")
    OUT.write_text(html.replace("__DATA__", lambda_safe(payload)), encoding="utf-8")
    print(f"wrote {OUT} ({OUT.stat().st_size/1024:.0f} KB): "
          f"{len(data['chapters'])} chapters, {len(data['guides'])} guides")


def lambda_safe(s: str) -> str:
    # str.replace has no backslash-escape processing, this just documents intent
    return s


if __name__ == "__main__":
    main()
