package login;

import admin.ManagerController;
import admin.ManagerView;
import javafx.fxml.FXML;
import javafx.scene.control.ComboBox;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import root.RootController;
import root.RootView;
import seller.SellerView;
import util.DAO;

import javax.swing.*;

import java.sql.ResultSet;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

import static javax.swing.JOptionPane.showMessageDialog;

/**
 * 登录界面控制器类，包含处理事件的方法
 */
public class LoginController {
    /**
     * 用户类型下拉列表组件
     */
    @FXML
    private ComboBox<String> userType;
    /**
     * 账号文本框组件
     */
    @FXML
    private TextField account;
    /**
     * 密码文本框组件
     */
    @FXML
    private PasswordField pwd;

    /**
     * 初始化用户类型下拉列表，提供用户选项超级管理员、管理员、售票员，
     * 默认选择售票员登录
     */
    @FXML
    private void initialize() {
        userType.getItems().addAll("超级管理员","管理员","售票员");
        userType.getSelectionModel().select(2);
        account.setText("seller1");
        pwd.setText("seller1");
    }

    /**
     * 登录按钮触发事件，进行登录判定
     */
    @FXML
    private void onLogin() {
        //输入账号
        String account = this.account.getText();
        //输入密码
        String pwd = this.pwd.getText();
        //选择的用户类型，0：超级管理员，1：管理员，2：售票员
        int userType = this.userType.getSelectionModel().getSelectedIndex();
        //账号或密码为空，提示
        if (account.isEmpty() || pwd.isEmpty()) {
            showMessageDialog(null, "账号或密码为空！", "提示", JOptionPane.ERROR_MESSAGE);
        }
        //已输入账号密码，进行登录判定
        else {
            //查询数据库，获取指定账号信息
            ResultSet re = DAO.getInstance().getAccountInfo(account);
            //捕获下层数据库异常，提示信息
            if (re == null) {
                showMessageDialog(null, "加载数据出错！", "提示", JOptionPane.ERROR_MESSAGE);
                return;
            }
            //若存在且密码正确则更新最后登录时间，并切换窗口，否则提示用户账号或密码错误
            try {
                //账号不存在或账号类型不匹配或密码错误，提示账号或密码错误
                if (!re.next() || !(re.getInt("idtype") == userType && re.getString("pwd").equals(pwd))) {
                    showMessageDialog(null, "账号或密码错误！", "提示", JOptionPane.ERROR_MESSAGE);
                }
                else {
                    //更新该账号的登录时间
                    DAO.getInstance().updateLoginTime(account, LocalDateTime.now().format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss")));
                    //0:超级管理员，1:管理员，2:售票员
                    switch (re.getInt("idtype")) {
                        case 0:
                            RootView rootView = new RootView();
                            //记录当前登录的账号信息
                            RootController.account = account;
                            rootView.showWindow();
                            break;
                        case 1:
                            ManagerView managerView = new ManagerView();
                            //记录当前登录的账号信息
                            ManagerController.account = account;
                            managerView.showWindow();
                            break;
                        case 2:
                            SellerView sellerView = new SellerView();
                            sellerView.showWindow();
                            break;
                    }
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    /**
     * 退出按钮触发事件，关闭界面
     */
    @FXML
    private void onExit() {
        System.out.println("退出系统");
        LoginView.getStage().close();
    }
}
