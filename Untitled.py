
# coding: utf-8

# In[7]:


from scipy.io import loadmat
import numpy as np


# In[8]:


x = np.squeeze(loadmat('rel_seq.mat')['s10'])


# In[9]:


for i in x:
    print(i, end=", ")

