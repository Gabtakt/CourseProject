package root;

import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ButtonType;
import javafx.scene.control.TextField;
import util.DAO;

import javax.swing.*;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Optional;

import static javax.swing.JOptionPane.showMessageDialog;

public class DeleteAccountController {
    @FXML
    private TextField DEL_ACCOUNT;
    @FXML
    private Button DeleteButton;
    @FXML
    private Button CloseButton;

    public static String account;
    @FXML
    private void initialize() {

    }
    @FXML
    private void onChooseDeleteButton() {
        String account = DEL_ACCOUNT.getText();
        //如果删除的账号是当前登录账号，不允许删除
        if (account.equals(DeleteAccountController.account)) {
            showMessageDialog(null, "当前账号已登录！", "提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (account.isEmpty()) {
            showMessageDialog(null, "未输入账号！", "提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        ResultSet re = DAO.getInstance().getAccountInfo(account);
        if (re == null) {
            showMessageDialog(null, "数据访问异常！", "提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        try {
            if (!re.next()) {
                showMessageDialog(null, "账号不存在！", "提示", JOptionPane.ERROR_MESSAGE);
                return;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        Alert alert = new Alert(Alert.AlertType.CONFIRMATION);
        alert.setContentText(String.format("确认删除账号\"%s\"吗?",account));

        Optional<ButtonType> result = alert.showAndWait();
        if (result.get() == ButtonType.OK) {
            if (!DAO.getInstance().deleteAccountInfo(account)) {
                showMessageDialog(null, "删除账号失败！", "提示", JOptionPane.ERROR_MESSAGE);
            }
            else {
                showMessageDialog(null, "删除账号成功！", "提示", JOptionPane.INFORMATION_MESSAGE);
                //删除成功后，刷新账号列表
                RootController.getInstance().showList();
                DeleteAccountView.getStage().close();
            }
        }
        else {
            alert.close();
        }
    }
    @FXML
    private void onChooseCloseButton() {
        DeleteAccountView.getStage().close();
    }
}
