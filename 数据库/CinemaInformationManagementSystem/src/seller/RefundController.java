package seller;

import javafx.fxml.FXML;
import javafx.scene.control.TextField;
import util.DAO;
import util.Util;

import javax.swing.*;

import static javax.swing.JOptionPane.showMessageDialog;

public class RefundController {
    @FXML
    private TextField PH;

    @FXML
    private void initialize() {
        PH.setText("");
    }

    @FXML
    private void onOKButton() {
        if (!Util.isNumeric(PH.getText())) {
            showMessageDialog(null,"输入数字非法！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        int tid = Integer.parseInt(PH.getText());
        if (!DAO.getInstance().isTicket(tid)) {
            showMessageDialog(null,"电影票不存在！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (DAO.getInstance().isUsedTicket(tid)) {
            showMessageDialog(null,"电影票已使用！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (!DAO.getInstance().deleteTicketInfo(tid)) {
            showMessageDialog(null,"数据访问异常！","提示", JOptionPane.ERROR_MESSAGE);
            return;
        }
        showMessageDialog(null,"删除成功！","提示", JOptionPane.INFORMATION_MESSAGE);
        RefundView.getStage().close();
        SellerController.getInstance().renderSeatGraph();
    }
    @FXML
    private void onCloseButton() {
        RefundView.getStage().close();
    }
}
