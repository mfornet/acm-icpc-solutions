import re
print("No" if re.fullmatch("[a-z]{5}@hogwarts\.com", input()) is None else "Yes")
