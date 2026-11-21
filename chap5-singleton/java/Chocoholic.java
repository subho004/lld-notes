/** Client of the enum singleton: both references are the same INSTANCE. */
public class Chocoholic {
    public static void main(String[] args) {
        ChocoholicEnum.INSTANCE.eatChocolate();
        ChocoholicEnum another = ChocoholicEnum.INSTANCE;
        System.out.println("Same instance? " + (ChocoholicEnum.INSTANCE == another));
    }
}
