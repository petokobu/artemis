class Error:
    def __init__(self, errmess: str, **meta):
        self.esub               = "error"
        self.wsub               = "warning"
        self.errmess            = errmess
        self.origin: str | None = meta.get("origin", None)
        self.reason: str | None = meta.get("reason", None)

    def warn(self) -> None:
        print(f"{self.wsub}:" if self.origin is None
              else f"{self.wsub} at {self.origin}:")
        for line in errmess.split("\n"):
            print(f"\t{line.rstrip()}")
        if self.reason is not None:
            print("\treason:")
            for line in self.reason.split("\n"):
                print(f"\t\t{line.rstrip()}")

    def fatal(self) -> None:
        print(f"{self.esub}:" if self.origin is None
              else f"{self.esub} at {self.origin}:")
        for line in errmess.split("\n"):
            print(f"\t{line.rstrip()}")
        if self.reason is not None:
            print("\treason:")
            for line in self.reason.split("\n"):
                print(f"\t\t{line.rstrip()}")


class ParsingError(Error):
    def __init__(self, errmess: str, **meta):
        super().__init__(errmess, meta)
        self.esub = "syntax error"
        self.wsub = "syntax warning"


class IoError(Error):
    def __init__(self, errmess: str, **meta):
        super().__init__(errmess, meta)
        self.esub = "i/o error"
        self.wsub = "i/o warning"


class ObjectError(Error):
    def __init__(self, errmess: str, **meta):
        super().__init__(errmess, meta)
        self.esub = "object error"
        self.wsub = "object warning"

