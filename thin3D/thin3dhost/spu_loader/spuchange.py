# Copyright (c) 2001, Stanford University
# All rights reserved.
#
# See the file LICENSE.txt for information on redistributing this software.

import sys
sys.path.append( "../glapi_parser" )
import apiutil


apiutil.CopyrightC()

print """

/* DO NOT EDIT - THIS FILE AUTOMATICALLY GENERATED BY spuchange.py SCRIPT */

#include "cr_spu.h"
#include "cr_error.h"

void crSPUChangeInterface( SPUDispatchTable *table, void *orig_func, void *new_func )
{
	struct _copy_list_node *temp;
	if (table->mark == 1)
	{
		return;
	}
	if (orig_func == new_func) 
	{
		return;
	}
	table->mark = 1;
"""

keys = apiutil.GetDispatchedFunctions()
for func_name in keys:
	print '\tif ((void *)table->%s == orig_func)' % func_name
	print '\t{'
	print '\t\ttable->%s = (%sFunc_t)new_func;' % (func_name, func_name)
	print '\t\tfor (temp = table->copyList ; temp ; temp = temp->next)'
	print '\t\t{'
	print '\t\t\tcrSPUChangeInterface( temp->copy, orig_func, new_func );'
	print '\t\t}'
	print '\t}'

print """
	if (table->copy_of != NULL)
	{
		crSPUChangeInterface( table->copy_of, orig_func, new_func );
	}
	for (temp = table->copyList ; temp ; temp = temp->next)
	{
		crSPUChangeInterface( temp->copy, orig_func, new_func );
	}
	table->mark = 0;
"""
print '}'

print """
void crSPUChangeDispatch(SPUDispatchTable *dispatch, const SPUNamedFunctionTable *newtable)
{
    SPUGenericFunction func;
"""
keys = apiutil.GetDispatchedFunctions()
for func_name in keys:
    print '\tfunc = crSPUFindFunction(newtable, "%s");' % func_name
    print '\tif (func && ((SPUGenericFunction)dispatch->%s!=func))' % func_name
    print '\t{'
    print '\t\tcrDebug("%%s changed from %%p to %%p", "gl%s", dispatch->%s, func);' % (func_name, func_name)
    print '\t\tcrSPUChangeInterface(dispatch, dispatch->%s, func);' % func_name
    print '\t}\n'
print """
}
"""
