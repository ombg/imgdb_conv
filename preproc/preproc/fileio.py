

def read_txt_file(txt):
  """Reads a txt file line by line.

  Args:
    txt: The text file to be read
  Returns:
    file_list: list of strings.
  """
  f = open(txt, 'r')
  file_list = []
  for txtline in f:
    file_list.append(txtline)

  return file_list


def write_txt_file(txt, txt_list):
  """Writes a list of strings to a txt file line by line.

  Args:
    txt: The text file to be written to
  Returns:
    txt_list: list of strings.
  """
  file = open(txt, 'w')

  for item in txt_list:
    file.write("%s" % item)
