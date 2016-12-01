# See
# https://www.tensorflow.org/versions/r0.10/get_started/basic_usage.html
# for details.
#import gzip
import os
#import re
import sys
import tarfile

from six.moves import urllib
import tensorflow as tf
#from tensorflow.models.image.cifar10 import cifar10

FLAGS = tf.app.flags.FLAGS

# Basic model parameters.
tf.app.flags.DEFINE_string('data_dir', '../cifar10_data',
                           """Path to the CIFAR-10 data directory.""")
tf.app.flags.DEFINE_string('train_dir','../cifar10_train',
                    """Directory where to write event logs """
                    """and checkpoint.""")
tf.app.flags.DEFINE_integer('batch_size', 100, 'Batch size. '
                     'Must divide evenly into the dataset sizes')
tf.app.flags.DEFINE_boolean('use_fp16', False,
                            """Train the model using fp16.""")

DATA_URL = 'http://www.cs.toronto.edu/~kriz/cifar-10-binary.tar.gz'


def train():
  # model will be built into the default graph. Why?
  with tf.Graph().as_default():

    # Get images and labels for CIFAR-10
    # Labels: int32 value between 0..9
    images, labels = cifar10.distorted_inputs()


    #This must be replaced with my method. Output should be the same.
    #logits: Classifier output, 10-dim vector per label with logits
    print('om:images: {}'.format(images))

def maybe_download_and_extract():
  """Download and extract the tarball from Alex's website."""
  dest_directory = FLAGS.data_dir
  if not os.path.exists(dest_directory):
    os.makedirs(dest_directory)
  filename = DATA_URL.split('/')[-1]
  filepath = os.path.join(dest_directory, filename)
  if not os.path.exists(filepath):
    def _progress(count, block_size, total_size):
      sys.stdout.write('\r>> Downloading %s %.1f%%' % (filename,
                                                       float(count * block_size) / float(total_size) * 100.0))
      sys.stdout.flush()

    filepath, _ = urllib.request.urlretrieve(DATA_URL, filepath, _progress)
    print()
    statinfo = os.stat(filepath)
    print('Successfully downloaded', filename, statinfo.st_size, 'bytes.')
    tarfile.open(filepath, 'r:gz').extractall(dest_directory)

# If named main it seems to be callable by TF.
def main(argv=None):
  print('Hello')
  maybe_download_and_extract()
  if tf.gfile.Exists(FLAGS.train_dir):
    tf.gfile.DeleteRecursively(FLAGS.train_dir)
  tf.gfile.MakeDirs(FLAGS.train_dir)
  # train()


if __name__ == '__main__':
  tf.app.run()



