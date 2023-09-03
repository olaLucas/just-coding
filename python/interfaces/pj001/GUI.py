import tkinter
import customtkinter

customtkinter.set_appearance_mode("System")
customtkinter.set_default_color_theme("blue")

class gui(customtkinter.CTk):
    def __init__(self) -> None:
        super().__init__()

        self.x_window_size = 1100
        self.y_window_size = 580

        self.geometry(f"{self.x_window_size}x{self.y_window_size}")

        self.grid_columnconfigure((1), weight=1)
        self.grid_rowconfigure((0,1), weight=1)


        self.left_frame = customtkinter.CTkFrame(self)
        self.radioButton_frame = customtkinter.CTkFrame(self)
        self.checkBox_frame = customtkinter.CTkFrame(self)
        self.tabView_frame = customtkinter.CTkFrame(self)
        self.progressBar_frame = customtkinter.CTkFrame(self, fg_color="transparent")

        self.left_frame.grid(row=0, rowspan=3, column=0, padx=10, pady=10, sticky="nsew")
        self.radioButton_frame.grid(row=0, column=3, padx=10, pady=10, sticky="nsew")
        self.checkBox_frame.grid(row=1, column=3, padx=10, pady=10, sticky="nsew")
        self.progressBar_frame.grid(row=1, column=1, columnspan=2, padx=10, pady=10, sticky="nsew")


        self.left_UPLabel = customtkinter.CTkLabel(self.left_frame, text="CustomTkinter")
        self.left_UPLabel.grid(row=1, column=0, padx=10, pady=10)

        self.left_firstButton = customtkinter.CTkButton(self.left_frame, text="CtkButton")
        self.left_firstButton.grid(row=2, padx=10, pady=10)

        self.left_secondButton = customtkinter.CTkButton(self.left_frame, text="CtkButton")
        self.left_secondButton.grid(row=3, padx=10, pady=10)

        self.left_thirdButton = customtkinter.CTkButton(self.left_frame, text="Disabled CTkButton", state="Disabled")
        self.left_thirdButton.grid(row=4, padx=10, pady=10)

        self.left_appearance_label = customtkinter.CTkLabel(self.left_frame, text="Apperance mode:")
        self.left_appearance_label.grid(row=5, padx=10, pady=10)

        self.left_appearance_OptionMenu = customtkinter.CTkOptionMenu(self.left_frame, values=["Dark", "Light"])
        self.left_appearance_OptionMenu.grid(row=6, padx=10, pady=10)

        self.left_UIScalling_Label = customtkinter.CTkLabel(self.left_frame, text="UI Scaling:")
        self.left_UIScalling_Label.grid(row=7, padx=10, pady=10)

        self.left_UIScalling_OptionMenu = customtkinter.CTkOptionMenu(self.left_frame, values=["100%", "150%", "200%"])
        self.left_UIScalling_OptionMenu.grid(row=8, padx=10, pady=10)


        self.tabGroup_tab = customtkinter.CTkTabview(self)
        self.tabGroup_tab.add("Tab 1")
        self.tabGroup_tab.add("Tab 2")
        self.tabGroup_tab.add("Tab 3")
        self.tabGroup_tab.grid(row=0, column=2, padx=10, pady=10, sticky="nsew")
        self.tabGroup_tab.tab("Tab 1").grid_columnconfigure(0, weight=1)
        
        self.tabGroup_optionMenu = customtkinter.CTkOptionMenu(self.tabGroup_tab.tab("Tab 1"), values=["CTkOptionMenu"])
        self.tabGroup_optionMenu.grid(row=0, column=0, padx=10, pady=10)

        self.tabGroup_comboBox = customtkinter.CTkComboBox(self.tabGroup_tab.tab("Tab 1"), values=["CTkComboBox"])
        self.tabGroup_comboBox.grid(row=1, column=0, padx=10, pady=10)

        self.tabGroup_InputDialogButton = customtkinter.CTkButton(self.tabGroup_tab.tab("Tab 1"), text="Open CTk Input Dialog")
        self.tabGroup_InputDialogButton.grid(row=2, column=0, padx=10, pady=10)


        self.radioButton_label = customtkinter.CTkLabel(self.radioButton_frame, text="CtkRadioButton Group:")
        self.radioButton_label.grid(row=1, padx=10, pady=10)

        self.radioButtonGroup_firstRadioButton = customtkinter.CTkRadioButton(self.radioButton_frame, text="CtkRadioButton")
        self.radioButtonGroup_firstRadioButton.grid(row=2, padx=10, pady=10)
        
        self.radioButtonGroup_secondRadioButton = customtkinter.CTkRadioButton(self.radioButton_frame, text="CtkRadioButton")
        self.radioButtonGroup_secondRadioButton.grid(row=3, padx=10, pady=10)
        
        self.radioButtonGroup_thirdRadioButton = customtkinter.CTkRadioButton(self.radioButton_frame, text="CtkRadioButton")
        self.radioButtonGroup_thirdRadioButton.grid(row=4, padx=10, pady=10)


        self.checkBoxGroup_firstCheckBox = customtkinter.CTkCheckBox(self.checkBox_frame, text="CTkCheckBox")
        self.checkBoxGroup_firstCheckBox.grid(row=1, column=0, padx=10, pady=10)

        self.checkBoxGroup_secondCheckBox = customtkinter.CTkCheckBox(self.checkBox_frame, text="CTkCheckBox")
        self.checkBoxGroup_secondCheckBox.grid(row=2, column=0, padx=10, pady=10)

        self.checkBoxGroup_firstSwitch = customtkinter.CTkSwitch(self.checkBox_frame, text="CTkSwitch")
        self.checkBoxGroup_firstSwitch.grid(row=3, column=0, padx=10, pady=10)

        self.checkBoxGroup_secondSwitch = customtkinter.CTkSwitch(self.checkBox_frame, text="CtkSwitch")
        self.checkBoxGroup_secondSwitch.grid(row=4, column=0, padx=10, pady=10)


        self.textbox = customtkinter.CTkTextbox(self)
        self.textbox.grid(row=0, column=1, padx=10, pady=10, sticky="nsew")

        self.entry = customtkinter.CTkEntry(self, placeholder_text="CtkEntry")
        self.entry.grid(row=2, column=1, columnspan=2, padx=10, pady=10, sticky="nsew")

        self.button = customtkinter.CTkButton(self, text="CtkButton")
        self.button.grid(row=2, column=3, padx=10, pady=10, sticky="nsew")


        self.progressBar_frame.grid_columnconfigure(0, weight=1)
        #self.progressBar_frame.grid_rowconfigure((0,1,2,3), weight=1)

        self.progressBar_frame_segButton = customtkinter.CTkSegmentedButton(self.progressBar_frame, values=["Value 1", "Value 2", "Value 3"])
        self.progressBar_frame_segButton.grid(row=0, column=0, padx=10, pady=10, sticky="new")

        self.progressBar_frame_progressBar1 = customtkinter.CTkProgressBar(self.progressBar_frame)
        self.progressBar_frame_progressBar1.grid(row=1, column=0, padx=10, pady=10, sticky="new")

        self.progressBar_frame_progressBar2 = customtkinter.CTkProgressBar(self.progressBar_frame)
        self.progressBar_frame_progressBar2.grid(row=2, column=0, padx=10, pady=10, sticky="new")

        self.progressBar_frame_slider1 = customtkinter.CTkSlider(self.progressBar_frame)
        self.progressBar_frame_slider1.grid(row=3, column=0, padx=10, pady=10, sticky="new")

        self.progressBar_frame_progressBar3 = customtkinter.CTkProgressBar(self.progressBar_frame, orientation="vertical")
        self.progressBar_frame_progressBar3.grid(row=0, rowspan=5, column=1, padx=10, pady=10, sticky="ns")

        self.progressBar_frame_slider2 = customtkinter.CTkSlider(self.progressBar_frame, orientation="vertical")
        self.progressBar_frame_slider2.grid(row=0, rowspan=5, column=2, padx=10, pady=10, sticky="ns") 


mainWindow = gui()
mainWindow.mainloop()