python-uniqid
=============

I've run into enough cases where I want to get the exact equivalent of `PHP's
uniqid function`_.

One snippet I found on the internet, `here`_, had imperfections, and appeared
to be slow. This was probably due to the fact that it did not actually
follow the implementation PHP used. So, I created this.

.. _PHP's uniqid function: http://php.net/uniqid
.. _here: http://gurukhalsa.me/2011/uniqid-in-python/
