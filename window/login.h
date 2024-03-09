GObject *entry_password;
GObject *entry_username;
GObject *label_username_error;
GObject *label_password_error;

void login_register();
void username_error();
void username_errorno();
void username_text_insert();
void username_text_delete();
void password_error();
void password_errorno();
void password_text_insert();
void password_text_delete();

int username_text_count = 0;
int password_text_count = 0;

void login_activate(GtkApplication *app, gpointer user_data){
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
	//define widgets
	GObject *btn_register = gtk_builder_get_object(builder, "btn_register");
	entry_username = gtk_builder_get_object(builder, "entry_username");
	entry_password = gtk_builder_get_object(builder, "entry_password");
	label_username_error = gtk_builder_get_object(builder, "label_username_error");
	label_password_error = gtk_builder_get_object(builder, "label_password_error");
	//connect signals to widgets
	g_signal_connect(btn_register, "clicked", G_CALLBACK(login_register), NULL);
	g_signal_connect(gtk_editable_get_delegate(GTK_EDITABLE(entry_username)), "insert-text", G_CALLBACK(username_text_insert), NULL);
	g_signal_connect(gtk_editable_get_delegate(GTK_EDITABLE(entry_username)), "delete-text", G_CALLBACK(username_text_delete), NULL);
	g_signal_connect(gtk_editable_get_delegate(GTK_EDITABLE(entry_password)), "insert-text", G_CALLBACK(password_text_insert), NULL);
	g_signal_connect(gtk_editable_get_delegate(GTK_EDITABLE(entry_password)), "delete-text", G_CALLBACK(password_text_delete), NULL);
	//show window
	gtk_widget_set_visible(GTK_WIDGET(window), TRUE);
}

void login_register(){
	GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(entry_username));
	const char *username = gtk_entry_buffer_get_text(buffer);
	buffer = gtk_entry_get_buffer(GTK_ENTRY(entry_password));
	const char *password = gtk_entry_buffer_get_text(buffer);
	if(strlen(username) >= 5){
		if(strlen(password) >= 8){
			int status = db_user_register(username, password);
			if(status == DB_STATE_EXISTS){
				username_error("User already exists");
			}else if(status == DB_STATE_SUCCESS){
				//TODO go to home window
			}
		}else
			password_error("Password must be at least 8 characters");
	}else
		username_error("Username must be at least 5 characters");
	
}

void username_error(char *text){
	gtk_widget_set_visible(GTK_WIDGET(label_username_error), TRUE);
	gtk_label_set_text(GTK_LABEL(label_username_error), text);
	gtk_widget_add_css_class(GTK_WIDGET(entry_username), "entry-error");
}
void username_errorno(){
	gtk_widget_set_visible(GTK_WIDGET(label_username_error), FALSE);
	gtk_widget_remove_css_class(GTK_WIDGET(entry_username), "entry-error");
}
void username_text_insert(){
	username_text_count++;
	if(username_text_count >= 5)
		username_errorno();
	
}
void username_text_delete(){
	username_text_count--;
}
void password_error(char *text){
	gtk_widget_set_visible(GTK_WIDGET(label_password_error), TRUE);
	gtk_label_set_text(GTK_LABEL(label_password_error), text);
	gtk_widget_add_css_class(GTK_WIDGET(entry_password), "entry-error");
}
void password_errorno(){
	gtk_widget_set_visible(GTK_WIDGET(label_password_error), FALSE);
	gtk_widget_remove_css_class(GTK_WIDGET(entry_password), "entry-error");
}
void password_text_insert(){
	password_text_count++;
	if(password_text_count >= 8)
		password_errorno();
}
void password_text_delete(){
	password_text_count--;
}
