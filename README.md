# **FED**

_**fed**_ is a command line tool for saving and accessing your favourite folders via the terminal.

## **Usage**

There are two options to work with folders: via list numbers and aliases.

### **add**

Add directories that you like or use '.' to add the current directory to your favourites.
Use **-a [alias] [directory]** to add a folder with an alias to access it later.

```shell
$ fed add .
    E:\Scripts\fed directory is added to favourites.

$ fed add /home/
    fed: /home/ is already in favourites.

$ fed add -a python_projects E:\Python
    E:\Python directory is added to favourites.

$ fed add C: E: C:\Users
    fed: C: is already in favourites.
    E: directory is added to favourites.
    C:\Users directory is added to favourites.
```

### **ls**

List all your favourite directories or the number you like.
Aliases are shown in [] braces.

```shell
$ fed ls
    fed: Favourite folders:

    1. C:
    2. E:\Scripts\fed
    3. E:
    4. [python_projects] E:\Python

    Use the number with fed <cd> command to cd into the selected directory

$ fed ls 2
    fed: Favourite folders:

    1. C:
    2. E:\Scripts\fed

    Use the number with fed <cd> command to cd into the selected directory
```

### **cd**

Since it is impossible to move from the directory the program was run at, fed copies the commands to the user's clipboard. That way, using Ctrl + V a user can then navigate to the favourite folder without typing the whole root. Use the number in the list of favourite folders or folder alias for quick access to 'cd' command.

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

$ fed cd python_projects
    fed: E:\Desktop is your directory.

    The command <E: && cd E:\Python> is copied to your clipboard.
    Use Ctr+V to get the command.

$ E: && cd E:\Python
```

### **clean**

Removes the folder from favourites. Use 'all' for full cleanup and '.' to remove the current folder.
The folder can also be cleaned up by the number it is on the list or using the given folder alias.

```shell
$ fed clean all
    fed: favourite folders are now empty.

$ fed clean .
    fed: The directory E:\Scripts\fed is deleted from favourites.

$ fed clean /home/Desktop /home/fed
    fed: The directory /home/Desktop is deleted from favourites.
    fed: The directory /home/fed is not in favourites.

$ fed clean 1
    fed: The directory C: is deleted from favourites.

$ fed clean python_projects
    fed: The directory [python_projects] E:\Desktop is deleted from favourites.
```

### **open**

Opens given folder in explorer. Can take either alias or a number in the favourites list.

```shell
$ fed open nvim 
    fed: openning C:\Users\admin\AppData\Local\nvim directory.

$ fed open 1
    fed: openning C: directory.
```

### **rename**

Renames aliases for favourite directories.
```shell
$ fed rename fed fed_project
    fed: The directory    E:\Programming\fed alias is changed
    fed -> fed_project

$ fed rename git github
    fed: The directory git is not in favourites.
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
