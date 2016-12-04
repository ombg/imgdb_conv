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
# What is the difference to the following?
#model = tf.global_variables_initializer()

sess = tf.Session()

sess.run(model)
coord = tf.train.Coordinator()
threads = tf.train.start_queue_runners(sess=sess, coord=coord)

try:
  while not coord.should_stop():
    # Run training or whatever
    ex, lbl = sess.run([img, label])
    print(lbl)

except tf.errors.OutOfRangeError:
  print('Done training -- epoch limit reached')
finally:
  #When done, ask the threads to stop
  coord.request_stop()

# Wait for threads to finish
coord.join(threads)
sess.close()
