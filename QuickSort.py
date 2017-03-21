class QuickSort(Command):
	"""QuickSort Object"""	
	def __init__(self, lista):
		self.lista = lista
	
	def execute(self, lista):
		print "Imprimindo lista desordenada:"
		print lista
		print ""

		if len(lista) &gt; 1:
            pivot_index = len(lista) / 2
            smaller_lista = []
            larger_lista = []

            for i, val in enumerate(lista):
                    if i != pivot_index:
                            if val &lt; lista[pivot_index]:
                                    smaller_lista.append(val)
                            else:
                                    larger_lista.append(val)

            quick_sort(smaller_lista)
            quick_sort(larger_lista)
            lista[:] = smaller_lista + [lista[pivot_index]] + larger_lista

        print "Imprimindo lista ordenada:"
		print lista
		print ""
		