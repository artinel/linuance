static void login_activate(GtkApplication *app, gpointer user_data){
	//load ui file
	GtkBuilder *builder = load_ui(LOGIN_WINDOW_UI);
	//get window widget
	GObject *window = gtk_builder_get_object(builder, LOGIN_WINDOW);
	//config window
	gtk_window_set_default_size(GTK_WINDOW(window), LOGIN_WINDOW_WIDTH, LOGIN_WINDOW_HEIGHT);
	gtk_window_set_title(GTK_WINDOW(window), LOGIN_WINDOW_TITLE);
	gtk_window_set_resizable(GTK_WINDOW(window), LOGIN_WINDOW_RESIZABLE);
	//set app to window
	gtk_window_set_application(GTK_WINDOW(window), app);
	//load css
	load_css(GTK_WIDGET(window), CSS_GLOBAL);
	//show window
	gtk_widget_set_visible(GTK_WIDGET(window), TRUE);
}
