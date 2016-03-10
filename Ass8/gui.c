#include<gtk/gtk.h>
void static call(GtkWidget *widget,gpointer data)
{
    g_print("%s \n",(gchar*) data);
}

int main(int agrc, char *agrv[])
{
    gtk_init(&agrc,&agrv);
    GtkWidget *window,*button,*vbox;
    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window,"delete-event",G_CALLBACK(gtk_main_quit),NULL);
    gtk_window_set_title(GTK_WINDOW(window),"two button");

    vbox=gtk_vbox_new(0,0);
    button=gtk_button_new_with_label("button 1");
    g_signal_connect(button,"clicked",G_CALLBACK(call),(gpointer) "BUTTON 1");
    gtk_box_pack_start(GTK_BOX(vbox),button,0,0,0);
    button=gtk_button_new_with_label("button 2");
    g_signal_connect(button,"clicked",G_CALLBACK(call),(gpointer) "BUTTON 2");
    gtk_box_pack_start(GTK_BOX(vbox),button,0,0,0);
    button=gtk_button_new_with_label("Close");
    g_signal_connect(button,"clicked",G_CALLBACK(call),(gpointer) "BUTTON 2");
    gtk_box_pack_start(GTK_BOX(vbox),button,0,0,0);
    gtk_container_set_border_width(GTK_CONTAINER(window),10);
    gtk_container_add(GTK_CONTAINER(window),vbox); 
    gtk_widget_show_all(window);
    gtk_main();
    return (0);
}