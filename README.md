# **FED**

_**fed**_ is a command line tool for saving and accessing your favourite folders via the terminal.

## **Usage**

### **add**

Add directories that you like or use '.' to add the current directory to your favourites.

```shell
$ fed add .
    E:\Scripts\fed directory is added to favourites.

$ fed add /home/
    fed: /home/ is already in favourites.

$ fed add C: E: C:\Users
    fed: C: is already in favourites.
    E: directory is added to favourites.
    C:\Users directory is added to favourites.
```

### **ls**

List all your favourite directories or the number you like.

```shell
$ fed ls
    fed: Favourite folders:

    1. C:
    2. E:\Scripts\fed
    3. E:
    4. C:\Users

    Use the number with fed <cd> command to cd into the selected directory

$ fed ls 2
    fed: Favourite folders:

    1. C:
    2. E:\Scripts\fed

    Use the number with fed <cd> command to cd into the selected directory
```

### **cd**

Since it is impossible to move from the directory the program was run at, fed copies the commands to the user's clipboard. That way, using Ctrl + V a user can then navigate to the favourite folder without typing the whole root. Use the number in the list of favourite folders for quick access to 'cd' command.

-   For Windows, moving between drives requires additional command like 'C: ' before cd

```shell
$ fed cd 2
    fed: /home/ is your directory.

    The command <cd /home/> is copied to your clipboard.
    Use Ctr+V to get the command.

$ cd /home/

$ fed cd 1
    fed: C:\Users is your directory.

    The command <C: && cd C:\Users> is copied to your clipboard.
    Use Ctr+V to get the command.

$ C: && cd C:\Users
```

### **clean**

Remove folder from favourities. Use 'all' for full cleanup and '.' to remove the current folder.

```shell
$ fed clean all
    fed: favourite folders are now empty.

$ fed clean .
    fed: The directory E:\Scripts\fed is deleted from favourites.

$ fed clean /home/Desktop /home/fed
    fed: The directory /home/Desktop is deleted from favourites.
    fed: The directory /home/fed is not in favourites.
```

### **help**

Receive info for all available commands.

```shell
$ fed help

$ fed -h

$ fed --help
```

## **License**

[MIT License](https://choosealicense.com/licenses/mit/)
