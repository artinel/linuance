#include<gtk/gtk.h>
//include database
#include"include/database.h"
//include configs
#include"include/css_config.h"
#include"include/window_config.h"
//include utils
#include"include/utils.h"
//include window
#include"window/login.h"


int main(int argc, char *argv[]){
	//init database
	db_init();
	//TODO change app id
	GtkApplication *app = gtk_application_new("t.t.t", G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect(app, "activate", G_CALLBACK(login_activate), NULL);
	return g_application_run(G_APPLICATION(app), argc, argv);
	
}
