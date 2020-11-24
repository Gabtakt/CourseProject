package seller;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class RefundView extends Application {
    private static Stage stage = new Stage();

    @Override
    public void start(Stage primaryStage) throws Exception{
        stage = primaryStage;
        Parent root = FXMLLoader.load(getClass().getResource("refund.fxml"));
        primaryStage.setTitle("退票");
        primaryStage.setScene(new Scene(root));
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }

    public void showWindow() throws Exception{
        start(stage);
    }

    public static Stage getStage() {
        return stage;
    }
}
