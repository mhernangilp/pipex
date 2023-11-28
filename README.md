<h1 align="center">
	🛠️ pipex
</h1>

<p align="center">
	<b><i>Unix mecanism</i></b><br>
</p>

<h3 align="center">
	<a href="#%EF%B8%8F-about">About</a>
	<span> · </span>
	<a href="#%EF%B8%8F-usage">Usage</a>
	<span> · </span>
	<a href="#-testing">Testing</a>
</h3>

---

## 💡 About the project

> _This project will allow you to discover, through its use in your program,
the operation of a UNIX mechanism that you are already familiar with._


For more detailed information, look at the [**subject of this project**](https://github.com/mhernangilp/pipex/blob/main/es.subject.pipex.pdf).


## 🛠️ Usage

### Requirements

The function is written in C language and thus needs the **`gcc` compiler** and some standard **C libraries** to run.

### Instructions

**1. Compiling**

To compile, go to the project path and run:

```shell
$ make
```


## 📋 Testing

This program will replicate the behaviour of the next shell command:

```shell
$ < file1 cmd1 | cmd2 > file2
```

To test the program you just need to launch "pipex" with this parameters:

```shell
$ ./pipex file1 cmd1 cmd2 file2
```

In the bonus part the program can handle multiple pipes:

```shell
$ < file1 cmd1 | cmd2 | cmd3 | ... | cmdn > file2
```

To test the program you just need to launch "pipex" with this parameters:

```shell
$ ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
```

Also in the bonus part the program can handle << and >> redirections:

```shell
$ cmd1 << LIMITER | cmd2 >> file2
```

To test the program you just need to launch "pipex" with this parameters:

```shell
$ ./pipex here_doc LIMITER cmd1 cmd2 file2
```
