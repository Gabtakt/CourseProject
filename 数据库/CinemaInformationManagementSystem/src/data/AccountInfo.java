package data;

import java.util.Date;

/**
 * 账号信息类
 */
public class AccountInfo {
    private String account;
    private String pwd;
    private String name;
    private String phone;
    private Integer userType;
    private String lastLoginTime;

    public AccountInfo() {}

    public AccountInfo(String account, String pwd, String name, String phone, Integer userType,String lastLoginTime) {
        this.account = account;
        this.pwd = pwd;
        this.name = name;
        this.phone = phone;
        this.userType = userType;
        this.lastLoginTime = lastLoginTime;
    }

    public String getAccount() {
        return account;
    }

    public void setAccount(String account) {
        this.account = account;
    }

    public String getPwd() {
        return pwd;
    }

    public void setPwd(String pwd) {
        this.pwd = pwd;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getPhone() {
        return phone;
    }

    public void setPhone(String phone) {
        this.phone = phone;
    }

    public Integer getUserType() {
        return userType;
    }

    public void setUserType(Integer userType) {
        this.userType = userType;
    }

    public String getLastLoginTime() {
        return lastLoginTime;
    }

    public void setLastLoginTime(String lastLoginTime) {
        this.lastLoginTime = lastLoginTime;
    }
}
