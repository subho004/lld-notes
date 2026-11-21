/**
 * Common Component interface for ducks, adapter, decorator and Flock (Composite);
 * also observable via QuackObservable.
 */
public interface Quackable extends QuackObservable {
    public void quack();
}
