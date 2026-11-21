#!/usr/bin/env python3
"""Serve this folder locally with SPA fallback: python3 serve.py [port]"""
import http.server, os, sys
os.chdir(os.path.dirname(os.path.abspath(__file__)))
class H(http.server.SimpleHTTPRequestHandler):
    def do_GET(self):
        p = self.translate_path(self.path.split('?')[0])
        if not os.path.exists(p) and '.' not in os.path.basename(p):
            self.path = '/index.html'
        super().do_GET()
port = int(sys.argv[1]) if len(sys.argv) > 1 else 8080
print(f'http://localhost:{port}')
http.server.ThreadingHTTPServer(('127.0.0.1', port), H).serve_forever()
