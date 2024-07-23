#include <gtk/gtk.h>
#include <cairo.h>
#include <cmath>

static void do_drawing(cairo_t *cr) {
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, 1.5);

    double xMin = -10.0;
    double xMax = 10.0;
    double yMin = 0.0;
    double yMax = 100.0;

    int width = 800;
    int height = 600;

    cairo_translate(cr, width / 2, height / 2);
    cairo_scale(cr, width / (xMax - xMin), -height / (yMax - yMin));

    cairo_move_to(cr, xMin, 0);
    cairo_line_to(cr, xMax, 0);
    cairo_move_to(cr, 0, yMin);
    cairo_line_to(cr, 0, yMax);
    cairo_stroke(cr);

    cairo_set_source_rgb(cr, 1, 0, 0);

    for (double x = xMin; x <= xMax; x += 0.1) {
        double y = x * x;
        double screenX = x;
        double screenY = y;

        if (x == xMin) {
            cairo_move_to(cr, screenX, screenY);
        } else {
            cairo_line_to(cr, screenX, screenY);
        }
    }
    cairo_stroke(cr);
}

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    do_drawing(cr);
    return FALSE;
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *darea;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    darea = gtk_drawing_area_new();

    gtk_container_add(GTK_CONTAINER(window), darea);

    g_signal_connect(G_OBJECT(darea), "draw", G_CALLBACK(on_draw_event), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    gtk_window_set_title(GTK_WINDOW(window), "Graph of y = x^2");

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}

