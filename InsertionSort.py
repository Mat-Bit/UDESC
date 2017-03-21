class InsertionSort(Command):
	"""InsertionSort Object"""
	def __init__(self, lista):
		self.lista = lista
	
	def execute(self, lista):
		print "Imprimindo lista desordenada:"
		print lista
		print ""

		for i in range(1, len(lista)):
                j = i
                while j &gt; 0 and lista[j] &lt; lista[j-1]:
                        lista[j], lista[j-1] = lista[j-1], lista[j]
                        j -= 1

        print "Imprimindo lista ordenada:"
		print lista
		print ""