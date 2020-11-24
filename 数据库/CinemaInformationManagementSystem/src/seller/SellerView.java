package seller;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import login.LoginView;

public class SellerView extends Application {
    private Stage stage = new Stage();

    @Override
    public void start(Stage primaryStage) throws Exception{
        stage = primaryStage;
        Parent root = FXMLLoader.load(getClass().getResource("seller.fxml"));
        primaryStage.setTitle("售票子系统");
        primaryStage.setScene(new Scene(root));
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }

    public void showWindow() throws Exception{
        //LoginView.getStage().close();
        start(stage);
    }
}
