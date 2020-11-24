package data;

public class MovieScheduleInfo {
    private Integer room_id;
    private Tuple<String,String> timeTuple;

    public MovieScheduleInfo(Integer room_id, Tuple<String, String> timeTuple) {
        this.room_id = room_id;
        this.timeTuple = timeTuple;
    }

    public Integer getRoom_id() {
        return room_id;
    }

    public void setRoom_id(Integer room_id) {
        this.room_id = room_id;
    }

    public Tuple<String, String> getTimeTuple() {
        return timeTuple;
    }

    public void setTimeTuple(Tuple<String, String> timeTuple) {
        this.timeTuple = timeTuple;
    }

    @Override
    public String toString() {
        return "影厅号：" + room_id + "   观影时间：" + timeTuple.getP1() + "-" + timeTuple.getP2();
    }
}
