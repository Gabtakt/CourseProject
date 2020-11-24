package data;

/**
 * 电影信息类
 */
public class MovieInfo {
    private Integer mid;
    private String mname;
    private String mtime;
    private boolean screen;

    public MovieInfo(Integer mid, String mname, String time, boolean screen) {
        this.mid = mid;
        this.mname = mname;
        this.mtime = time;
        this.screen = screen;
    }

    public Integer getMid() {
        return mid;
    }

    public void setMid(Integer mid) {
        this.mid = mid;
    }

    public String getMname() {
        return mname;
    }

    public void setMname(String mname) {
        this.mname = mname;
    }

    public String getMtime() {
        return mtime;
    }

    public void setMtime(String mtime) {
        this.mtime = mtime;
    }

    public boolean isScreen() {
        return screen;
    }

    public void setScreen(boolean screen) {
        this.screen = screen;
    }
}
