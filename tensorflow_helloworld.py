
import tensorflow as tf

i = 8
x = tf.constant(1, name='x')
y = tf.Variable(x + 5, name='y')

model = tf.initialize_all_variables()

with tf.Session() as sess:

  sess.run(model)

  print(sess.run(y))
