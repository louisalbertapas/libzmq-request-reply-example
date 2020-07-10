#include <cstdlib>

int main(int argc, char *argv[])
{
    system("dbus-launch gnome-terminal -- \"./server\"");
    system("dbus-launch gnome-terminal -- \"./client\"");
}
