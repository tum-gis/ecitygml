namespace Ecitygml;

public enum ErrorKind : int
{
    InvalidArgument = 0,
    Io = 1,
    Parse = 2,
    UnresolvedReference = 3,
}