#include<gtk/gtk.h>

int main(int argc, char *argv[]){
	//TODO change app id
	GtkApplication *app = gtk_application_new("t.t.t", G_APPLICATION_DEFAULT_FLAGS);
	//TODO connect activate signal to app
	return g_application_run(G_APPLICATION(app), argc, argv);
	
}
