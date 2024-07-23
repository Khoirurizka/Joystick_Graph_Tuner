#include <gtk/gtk.h>

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *button_top;
    GtkWidget *hbox;
    GtkWidget *label_left;
    GtkWidget *label_right;
    GtkWidget *button_bottom;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "GTK+ Layout Example");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    button_top = gtk_button_new_with_label("Top Button");
    gtk_box_pack_start(GTK_BOX(vbox), button_top, FALSE, FALSE, 0);

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 0);

    label_left = gtk_label_new("Left Label");
    gtk_box_pack_start(GTK_BOX(hbox), label_left, TRUE, TRUE, 0);

    label_right = gtk_label_new("Right Label");
    gtk_box_pack_end(GTK_BOX(hbox), label_right, TRUE, TRUE, 0);

    button_bottom = gtk_button_new_with_label("Bottom Button");
    gtk_box_pack_start(GTK_BOX(vbox), button_bottom, FALSE, FALSE, 0);

    gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}

