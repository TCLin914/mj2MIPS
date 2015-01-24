
@.str = private constant [3 x i8] c"%d\00", align 1

declare i32 @printf(i8*, ...)

define void @main() {
entryBlock:
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([3 x i8]* @.str, i64 0, i64 0), i32 10)
  ret void
}

