#!/usr/bin/env python
# coding: utf-8

# In[38]:


import matplotlib.pyplot as plt
import pandas as pd


# In[48]:


df = pd.read_csv('times.csv')
map_df = df[df['Name'] == 'std::map']
tree_df = df[df['Name'] == 'TreeMap']
df.describe()


# In[69]:


fig, (ax_ins, ax_find) = plt.subplots(2, 1, figsize=(15, 5), sharey='row')

ax_ins.plot(map_df['numberOfElements'], map_df['insertionTime'], label='std::map')
ax_ins.plot(tree_df['numberOfElements'], tree_df['insertionTime'], label='TreeMap')
ax_ins.set_ylabel('Insertion time [ms]')

ax_find.plot(map_df['numberOfElements'], map_df['searchTime'], label='std::map')
ax_find.plot(tree_df['numberOfElements'], tree_df['searchTime'], label='TreeMap')
ax_find.set_ylabel('Search time [ms]')

handles, labels = ax_ins.get_legend_handles_labels()
fig.legend(handles, labels, loc='center right')

ax_find.set_xlabel('Number of elements')

fig.savefig('plt.png')
fig.show()


# In[19]:





# In[ ]:




