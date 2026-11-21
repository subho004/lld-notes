import java.util.List;
import java.util.ArrayList;

/**
 * Composite node: holds child MenuComponents (items or sub-menus) and treats them uniformly.
 */
public class Menu2 extends MenuComponent {
    List<MenuComponent> menuComponents = new ArrayList<MenuComponent>();
    String name;
    String description;

    public Menu2(String name, String description) {
        this.name = name;
        this.description = description;
    }

    public void add(MenuComponent menuComponent) {
        menuComponents.add(menuComponent);
    }

    public void remove(MenuComponent menuComponent) {
        menuComponents.remove(menuComponent);
    }

    public MenuComponent getChild(int i) {
        return menuComponents.get(i);
    }

    public String getName() {
        return name;
    }

    public String getDescription() {
        return description;
    }

    // Prints this menu's header, then delegates to each child; sub-menus recurse.
    public void print() {
        System.out.println(getName() + ", " + getDescription());
        System.out.println("--------------------------------");
        for (MenuComponent menuComponent : menuComponents) {
            menuComponent.print();
        }
    }
}
