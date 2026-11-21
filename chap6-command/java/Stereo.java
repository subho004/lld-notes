/**
 * Receiver: stereo with several operations (input selection, volume) that commands combine.
 */
public class Stereo {
    String location;

    public Stereo(String location) {
        this.location = location;
    }

    public Stereo() {
        this.location = "";
    }

    public void on() {
        System.out.println(location + " Stereo is on");
    }

    public void off() {
        System.out.println(location + " Stereo is off");
    }

    public void setCD() {
        System.out.println(location + " Stereo is set for CD input");
    }

    public void setDVD() {
        System.out.println(location + " Stereo is set for DVD input");
    }

    public void setRadio() {
        System.out.println(location + " Stereo is set for radio input");
    }

    public void setVolume(int volume) {
        System.out.println(location + " Stereo volume is set to " + volume);
    }
}
