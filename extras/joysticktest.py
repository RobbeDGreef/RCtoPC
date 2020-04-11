import tkinter
from tkinter import ttk
import pygame

pygame.init()
pygame.joystick.init()


class Main(tkinter.Frame):
    def __init__(self, parent, *args, **kwargs):
        tkinter.Frame.__init__(self, parent, *args, **kwargs)
        self.parent = parent

        self.joysticks = [pygame.joystick.Joystick(i) for i in range(pygame.joystick.get_count())]

        # To make a difference between joysticks with the same name
        self.joystick_names = []
        for i in range(pygame.joystick.get_count()):
            name = self.joysticks[i].get_name()
            if name in self.joystick_names:
                self.joystick_names.append(name + str(self.joystick_names.count(name)))

            else:
                self.joystick_names.append(name)

        self.current_joystick_ref = self.joysticks[0]
        self.current_joystick_ref.init()
        self._running = True

        self.setup()

    def changed_joystick(self, event):
        print("Changed to ", self.current_joystick_text.get())
        self.current_joystick_ref.quit()
        self.current_joystick_ref = self.joysticks[self.joystick_names.index(self.current_joystick_text.get())]
        self.current_joystick_ref.init()

    def setup(self):
        selectframe = tkinter.Frame(self.parent)

        self.current_joystick_text = tkinter.StringVar(self)
        self.current_joystick_text.set(self.joystick_names[0])

        joytext = tkinter.Label(selectframe, text="Current selected joystick:")
        options = tkinter.OptionMenu(selectframe, self.current_joystick_text, *self.joystick_names,
                                     command=self.changed_joystick)
        joytext.pack(side=tkinter.LEFT)
        options.pack(side=tkinter.LEFT)

        selectframe.pack()
        axisframe = tkinter.Frame(self.parent)
        axisframe.pack()

        xaxis_frame = tkinter.Frame(axisframe)
        self.xpb = ttk.Progressbar(xaxis_frame, orient="vertical", length=100, mode="determinate")
        self.xpb.pack()
        xtext = tkinter.Label(xaxis_frame, text="X")
        xtext.pack()
        xaxis_frame.pack(side=tkinter.LEFT)

        yaxis_frame = tkinter.Frame(axisframe)
        self.ypb = ttk.Progressbar(yaxis_frame, orient="vertical", length=100, mode="determinate")
        self.ypb.pack()
        ytext = tkinter.Label(yaxis_frame, text="Y")
        ytext.pack()
        yaxis_frame.pack(side=tkinter.LEFT)

    @staticmethod
    def remap(value):
        return (value - -1) * 100 / (1 - -1)

    def update_js(self):
        self.xpb['value'] = self.remap(self.current_joystick_ref.get_axis(0))
        self.ypb['value'] = self.remap(self.current_joystick_ref.get_axis(1))
        print("xpb: {} ypb: {}".format(self.current_joystick_ref.get_axis(0), self.current_joystick_ref.get_axis(1)))

    def stop(self):
        self._running = False

    def start(self):
        while self._running:
            pygame.event.pump()
            self.update_js()
            self.parent.update_idletasks()
            self.parent.update()

        self.parent.destroy()


if __name__ == '__main__':
    root = tkinter.Tk()
    m = Main(root)
    root.protocol("WM_DELETE_WINDOW", lambda: m.stop())
    m.pack(fill="both", expand=True)
    m.start()
