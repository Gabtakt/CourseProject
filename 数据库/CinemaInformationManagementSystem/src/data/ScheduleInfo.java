package data;

/**
 * 档期信息类
 */
public class ScheduleInfo {
    Integer schedule_id;
    Integer movie_id;
    String movie_name;
    Integer room_id;
    String show_time;
    String end_time;
    String show_date;
    Double normal_price;

    public ScheduleInfo(Integer schedule_id, Integer movie_id, String movie_name, Integer room_id, String show_time, String end_time, String show_date, Double normal_price) {
        this.schedule_id = schedule_id;
        this.movie_id = movie_id;
        this.movie_name = movie_name;
        this.room_id = room_id;
        this.show_time = show_time;
        this.end_time = end_time;
        this.show_date = show_date;
        this.normal_price = normal_price;
    }

    public Integer getSchedule_id() {
        return schedule_id;
    }

    public void setSchedule_id(Integer schedule_id) {
        this.schedule_id = schedule_id;
    }

    public Integer getMovie_id() {
        return movie_id;
    }

    public void setMovie_id(Integer movie_id) {
        this.movie_id = movie_id;
    }

    public String getMovie_name() {
        return movie_name;
    }

    public void setMovie_name(String movie_name) {
        this.movie_name = movie_name;
    }

    public Integer getRoom_id() {
        return room_id;
    }

    public void setRoom_id(Integer room_id) {
        this.room_id = room_id;
    }

    public String getShow_time() {
        return show_time;
    }

    public void setShow_time(String show_time) {
        this.show_time = show_time;
    }

    public String getEnd_time() {
        return end_time;
    }

    public void setEnd_time(String end_time) {
        this.end_time = end_time;
    }

    public String getShow_date() {
        return show_date;
    }

    public void setShow_date(String show_date) {
        this.show_date = show_date;
    }

    public Double getNormal_price() {
        return normal_price;
    }

    public void setNormal_price(Double normal_price) {
        this.normal_price = normal_price;
    }
}
