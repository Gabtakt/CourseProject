package root;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import login.LoginView;

public class RootView extends Application {
    private static Stage stage = new Stage();
    @Override
    public void start(Stage primaryStage) throws Exception{
        Parent root = FXMLLoader.load(getClass().getResource("root.fxml"));
        primaryStage.setTitle("账号管理子系统");
        primaryStage.setScene(new Scene(root));
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }

    public void showWindow() throws Exception{
        LoginView.getStage().close();
        start(stage);
    }

    public static Stage getInstance() {
        return stage;
    }
}
