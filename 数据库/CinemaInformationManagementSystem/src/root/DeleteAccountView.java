package root;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class DeleteAccountView extends Application {

    private static Stage stage = new Stage();
    @Override
    public void start(Stage primaryStage) throws Exception{
        Parent root = FXMLLoader.load(getClass().getResource("deleteAccount.fxml"));
        primaryStage.setTitle("删除账号");
        primaryStage.setScene(new Scene(root));
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }

    public void showWindow() throws Exception{
        start(stage);
    }

    /**
     * 获取界面的舞台实例
     * @return 舞台实例引用
     */
    public static Stage getStage() {
        return stage;
    }
}
