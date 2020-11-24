package login;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class LoginView extends Application {
    /**
     * 登录界面的舞台实例，用于界面切换
     */
    private static Stage stage = null;

    @Override
    public void start(Stage primaryStage) throws Exception{
        stage = primaryStage;
        Parent root = FXMLLoader.load(getClass().getResource("login.fxml"));
        primaryStage.setTitle("登录系统");
        primaryStage.setScene(new Scene(root));
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }

    /**
     * 获取登录界面的舞台实例
     * @return 舞台实例引用
     */
    public static Stage getStage() {
        return stage;
    }
}
