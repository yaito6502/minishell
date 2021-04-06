#!/bin/bash
SUCCESS="quote is closed."
FAILURE="line is not closed."

#template
# diff <(./test ) <(echo $SUCCESS)
# diff <(./test ) <(echo $FAILURE)

diff <(./test "'test' \"string.\"") <(echo $SUCCESS)
diff <(./test "'t\"e\"s\"t' \"s'tring.\"") <(echo $SUCCESS)
diff <(./test "'t\"e\"s\"t \"s'tring.\"\"") <(echo $SUCCESS)
diff <(./test "t\"\"\'\"est st\"\"\"r\'ing.") <(echo $SUCCESS)
diff <(./test "'t\"e\"s\"t \"s'tring.\"") <(echo $FAILURE)
diff <(./test "''''\"\"\"\"\"\"\"'''") <(echo $FAILURE)