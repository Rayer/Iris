# Iris Logger

## Requirements

### Log on console

Logs for console usually used by Unit Tests, and some server running events.

### Support syslog-ng

As literal

### Log on file stream

As literal

### Trigger logging when some event

When an event is sent, we need able to open specified logger(medium) for a specified time.

### Support ELK

As literal

### Support raw socket streaming

As literal, but it is quite optional.

### Support for multi-log intermedium.

We need to log to different medium, for example, log in console and file system.


## Design

We will have a MasterLogger as main logger, and this main logger have these functionality :

- Register Logger module, each logger implements some functionality such like console output, file stream...
- Able to de-register.
- Able to define logger group.
- Master logger provides LogLevel
- Master logger provides `TRACE`, `INFO`, `WARN`, and `ERROR`
- Able to read configuration from Database or File.
- <font color="red">**For phase 1, only Default Logger Group.**</font>

### Logger model

- Each model implements a specified functionality
- Can be registered to logger group


### Logger Group (Pending)

- Master logger have a default logger group
- All operation default comes to default logger group
- Logger can be set to other group, and can be set back to default logger group.
- Logger Group have itself message processor. This appender can process message before comes out. Default processor will print something like date and time..etc, and error appender should be print some like call stack...etc.