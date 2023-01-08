module com.example.demo {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires org.kordamp.bootstrapfx.core;

    opens View.ToyLangaugeGui to javafx.fxml;
    exports View.ToyLangaugeGui;
}