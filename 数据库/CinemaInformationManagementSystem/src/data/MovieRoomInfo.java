package data;

public class MovieRoomInfo {
    private Integer roomid;
    private String rname;
    private Integer row_num;
    private Integer column_num;
    private boolean useflag;

    public MovieRoomInfo(Integer roomid, String rname, Integer row_num, Integer column_num, boolean useflag) {
        this.roomid = roomid;
        this.rname = rname;
        this.row_num = row_num;
        this.column_num = column_num;
        this.useflag = useflag;
    }

    public Integer getRoomid() {
        return roomid;
    }

    public void setRoomid(Integer roomid) {
        this.roomid = roomid;
    }

    public String getRname() {
        return rname;
    }

    public void setRname(String rname) {
        this.rname = rname;
    }

    public Integer getRow_num() {
        return row_num;
    }

    public void setRow_num(Integer row_num) {
        this.row_num = row_num;
    }

    public Integer getColumn_num() {
        return column_num;
    }

    public void setColumn_num(Integer column_num) {
        this.column_num = column_num;
    }

    public boolean isUseflag() {
        return useflag;
    }

    public void setUseflag(boolean useflag) {
        this.useflag = useflag;
    }
}
