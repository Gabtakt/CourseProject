package data;

public class TicketInfo {
    private Integer tid;
    private Integer schedule_id;
    private Integer seat_row;
    private Integer seat_column;
    private Integer ticket_type;
    private boolean use_flag;
    private  Double ap;

    private String movieName;
    private Integer movieRoomID;

    public TicketInfo(Integer tid, Integer schedule_id, Integer seat_row, Integer seat_column, Integer ticket_type, boolean use_flag, Double ap) {
        this.tid = tid;
        this.schedule_id = schedule_id;
        this.seat_row = seat_row;
        this.seat_column = seat_column;
        this.ticket_type = ticket_type;
        this.use_flag = use_flag;
        this.ap = ap;
    }

    public Integer getTid() {
        return tid;
    }

    public void setTid(Integer tid) {
        this.tid = tid;
    }

    public Integer getSchedule_id() {
        return schedule_id;
    }

    public void setSchedule_id(Integer schedule_id) {
        this.schedule_id = schedule_id;
    }

    public Integer getSeat_row() {
        return seat_row;
    }

    public void setSeat_row(Integer seat_row) {
        this.seat_row = seat_row;
    }

    public Integer getSeat_column() {
        return seat_column;
    }

    public void setSeat_column(Integer seat_column) {
        this.seat_column = seat_column;
    }

    public Integer getTicket_type() {
        return ticket_type;
    }

    public void setTicket_type(Integer ticket_type) {
        this.ticket_type = ticket_type;
    }

    public boolean isUse_flag() {
        return use_flag;
    }

    public void setUse_flag(boolean use_flag) {
        this.use_flag = use_flag;
    }

    public Double getAp() {
        return ap;
    }

    public void setAp(Double ap) {
        this.ap = ap;
    }

    public String getMovieName() {
        return movieName;
    }

    public void setMovieName(String movieName) {
        this.movieName = movieName;
    }

    public Integer getMovieRoomID() {
        return movieRoomID;
    }

    public void setMovieRoomID(Integer movieRoomID) {
        this.movieRoomID = movieRoomID;
    }

    @Override
    public String toString() {
        return  String.format("票号：%06d,",tid) + "电影名：" + movieName + "," +
                "影厅号：" + movieRoomID + "," +
                String.format("座位号：%d排%d座,", seat_row, seat_column) +
                "票价：" + ap + "\n";
    }
}
