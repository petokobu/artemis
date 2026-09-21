import os
import sys
from pathlib import Path
from enum import StrEnum
from ..manifest.handle import Error, ParsingError, IoError, ObjectError


FW_DIR     = Path(...)
FW_SYS_DIR = FW_DIR/...
FW_USR_DIR = FW_DIR/...


class FWType(Enum):
    SYS = 0b01
    USR = 0b10


class ArgSet:
    def __init__(self) -> None:
        self.vital: bool    = False
        self.sys_dir: Path  = FW_SYS_DIR
        self.usr_dir: Path  = FW_USR_DIR
        self.fwtype: FWType = 0b00
        self.append: bool   = False


class Member(StrEnum):
    MAC  = "mac"
    IPV4 = "ipv4"
    IPV6 = "ipv6"
    PORT = "port"


class Class_(StrEnum):
    SRC = "src"
    DST = "dst"

    def __init__(self, member: Member) -> None:
        self.member = member


class Attribute(StrEnum):
    FLAG = "flag"


class Protocol(StrEnum):
    TCP  = "tcp"
    IPV4 = "ipv4"

    def __init__(self, attr: Attribute) -> None:
        self.attr = attr


class Item(StrEnum):
    ETHTYPE = "ethtype"
    PROTO   = "proto"
    TTL     = "ttl"
    TOS     = "tos"
    SEQ     = "seq"
    ACK     = "ack"
    RTT     = "rtt"


Object  = Class_ | Protocol | Item
Operand = Object | str


class Comparator(StrEnum):
    EQ  = "=="
    NEQ = "!="
    GT  = ">"
    GE  = ">="
    LT  = "<"
    LE  = "<="


class Relation:
    def __init__(self, op_a: Operand, op_b: Operand, comp: Comparator) -> None:
        self.op_a = op_a
        self.op_b = op_b
        self.comp = comp

    def eval(self) -> bool: ...


class Action(StrEnum):
    ACCEPT = "accept"
    BLOCK  = "block"
    REJECT = "reject"
    LOG    = "log"
    MODIFY = "modify"
    EXEC   = "exec"
    FWD    = "fwd"


ActionArg = Path


class Instruction:
    def __init__(self, action: Action, args: list[ActionArg],
                 next_action: Action | None = None): -> None:
        self.action      = action
        self.args        = args
        self.next_action = next_action


class RuleSet:
    def __init__(self, rel: Relation,
                 valid_branch: Relation | Instruction | None = None,
                 invalid_branch: Relation | Instruction | None = None) -> None:
        self.rel            = rel
        self.valid_branch   = valid_branch
        self.invalid_branch = invalid_branch


def load_bytecode() -> dict[str, int] | ParsingError:
# TODO
# purpose: loads the bytecode for VM instructions
# operation: reads vm.h and stores macros with instructions to a dictionary
# outcode: correctly loaded instruction values
# verification: if bytecodes are set incorrectly, return ParsingError
...


def parse(argset: ArgSet) -> RuleSet | ParsingError:
# TODO
# purpose: converts the contents of firewall definition files (*.fw) into an -
#       AST tree (RuleSet)
# operation: parses string text into conditions in RuleSet and instructions -
#       follow the syntax from lang.ebnf
# outcome: correctly and effectively build RuleSet, which is returned
# verification: checks syntax and the object logic, if incorrect, returns
#       ParsingError
...


def translate(ruleset: RuleSet, argset: ArgSet) -> Error | None:
# TODO
# purpose: translates AST to bytecode
# operation: walks the RuleSet, builds bytecode (based on bytecode.h) and -
#       saves the bytecode into a file
# outcome: bytecode readable by the VM (vm.c)
# verification: if the AST is not correct, return Error
...


def cmd() -> ArgSet | ParsingError:
    argset   = ArgSet()
    skip_cnt = 0
    for i, arg in enumerate(sys.argv):
        if skip_cnt:
            skip_cnt -= 1
            continue
        match arg:
            case "-v"|"--vital":
                argset.vital = True
            case "-u"|"--user-dir":
                if i + 1 == len(sys.argv):
                    return ParsingError(f"Expected a directory: {arg} DIR")
                try:
                    self.usr_dir = Path(sys.argv[i + 1]).resolve()
                except Exception as ex:
                    return ParsingError(f"Failed to resolve {arg} path",
                                        reason=f"{str(ex)}")
                skip_cnt     = 1
            case "-s"|"--user-dir":
                if i + 1 == len(sys.argv):
                    return ParsingError(f"Expected a directory: {arg} DIR")
                try:
                    self.sys_dir = Path(sys.argv[i + 1]).resolve()
                except Exception as ex:
                    return ParsingError(f"Failed to resolve {arg} path",
                                        reason=f"{str(ex)}")
                skip_cnt     = 1
            case "-U"|"--user":
                self.fwtype |= FWType.USR
            case "-S"|"--system":
                self.fwtype |= FWType.SYS
            case "-a"|"--append":
                self.append = True
            case _:
                return ParsingError(f"Unknown argument: {arg}")
    if argset.fwtype == 0b00:
        argset.fwtype = FWType.USR|FWType.SYS
    if argset.fwtype & FWType.USR:
        if not argset.usr_dir.is_dir():
            return IoError("Entered user directory is not a directory")
        if not os.access(argset.usr_dir, os.R_OK):
            return IoError("Entered user directory is not readable")
        if not os.access(argset.usr_dir, os.W_OK):
            return IoError("Entered user directory is not writable")
    if argset.fwtype & FWType.SYS:
        if not argset.sys_dir.is_dir():
            return IoError("Entered system directory is not a directory")
        if not os.access(argset.sys_dir, os.R_OK):
            return IoError("Entered system directory is not readable")
        if not os.access(argset.sys_dir, os.W_OK):
            return IoError("Entered system directory is not writable")
    return argset


def main() -> None:
    if isinstance((bytecode := load_bytecode()), ParsingError):
        argset.fatal()
        sys.exit(1)
    if isinstance((argset := cmd()), ParsingError):
        argset.fatal()
        sys.exit(1)
    if isinstance((ruleset := parse(argset)), ParsingError):
        if argset.vital:
            ruleset.fatal()
            sys.exit(1)
        ruleset.warn()
        sys.exit(0)
    if isinstance((res := translate(ruleset, argset)), Error):
        if argset.vital:
            res.fatal()
            sys.exit(1)
        res.warn()
        sys.exit(0)


if __name__ == "__main__":
    main()

