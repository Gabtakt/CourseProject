package root;

import data.AccountInfo;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import util.DAO;

public class RootController {
    @FXML
    private TableView<AccountInfo> AccountView;
    @FXML
    private TableColumn<AccountInfo,String> ZH;

    @FXML
    private TableColumn<AccountInfo,String> MM;

    @FXML
    private TableColumn<AccountInfo,String> XM;

    @FXML
    private TableColumn<AccountInfo,String> DH;

    @FXML
    private TableColumn<AccountInfo,Integer> ZHLX;

    @FXML
    private TableColumn<AccountInfo,String> SCDLSJ;

    private ObservableList<AccountInfo> list = FXCollections.observableArrayList();

    private static RootController instance = null;

    public static String account;

    @FXML
    private void initialize() {
        //初始化实例
        instance = this;
        //显示账号信息
        showList();
    }

   public void showList() {
        //每次显示先清除列表
        list.clear();
        //获取最新的账号信息列表
        list = DAO.getInstance().getAccountInfoList();
        if (list == null) {
            return;
        }
        //将数据映射到每一列
        ZH.setCellValueFactory(new PropertyValueFactory<>("account"));
        MM.setCellValueFactory(new PropertyValueFactory<>("pwd"));
        XM.setCellValueFactory(new PropertyValueFactory<>("name"));
        DH.setCellValueFactory(new PropertyValueFactory<>("phone"));
        ZHLX.setCellValueFactory(new PropertyValueFactory<>("userType"));
        SCDLSJ.setCellValueFactory(new PropertyValueFactory<>("lastLoginTime"));
        //将数据添加到表中
        AccountView.setItems(list);
    }

    @FXML
    private void onAddButton() throws Exception {
        AddAccountView addAccountView = new AddAccountView();
        addAccountView.showWindow();
    }

    @FXML
    private void onChangeButton() throws Exception {
        ChangeAccountView changeAccountView = new ChangeAccountView();
        changeAccountView.showWindow();
    }

    @FXML
    private void onDeleteButton() throws Exception {
        DeleteAccountView deleteAccountView = new DeleteAccountView();
        DeleteAccountController.account = account;
        deleteAccountView.showWindow();
    }

    @FXML
    private void onExitButton() {
        System.out.println("退出系统");
        RootView.getInstance().close();
    }

    public static RootController getInstance() {
        return instance;
    }
}
