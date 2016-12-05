

import tensorflow as tf
txt_list = "/Users/oliver/data/cache/test_png_full.txt"
# image_list = "/Users/oliver/data/cache/test_simple.txt"
# image_list = "/Users/oliver/data/tmp/0.png 6"

def read_txt_file(txt):

  f = open(txt, 'r')
  file_list =[]
  for txtline in f:
    file_list.append(txtline)

  return file_list

def read_my_file_format(filename_and_label_tensor):
  """Consumes a single filename and label as a ' '-delimited string.

  Args:
    filename_and_label_tensor: A scalar string tensor.

  Returns:
    Two tensors: the decoded image, and the int label.
  """
  # Stucture of one line in file list
  record_defaults = [[""], [""], [""], [""], [1]]

  # Parse line
  filename, d1, d2, d3, label = tf.decode_csv(filename_and_label_tensor,
                                  record_defaults=record_defaults,
                                  field_delim=" ")

  file_contents = tf.read_file(filename)
  example = tf.image.decode_png(file_contents)
  return example, label

image_list = read_txt_file(txt_list)

filename_queue = tf.train.string_input_producer(image_list)

img, label = read_my_file_format(filename_queue.dequeue())

model = tf.initialize_all_variables()

with tf.Session() as sess:

  sess.run(model)
  coord = tf.train.Coordinator()
  threads = tf.train.start_queue_runners(coord=coord)

  for i in range(5):
    ex, lbl = sess.run([img, label])
    print(lbl)

  coord.request_stop()
  coord.join(threads)

