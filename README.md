[formulamaslov.drawio](https://github.com/user-attachments/files/33566052/formulamaslov.drawio)
# Система мониторинга скорости перемешивания

## Постановка задачи
Программа предназначена для мониторинга технологического процесса в химическом реакторе по параметру «скорость перемешивания» (X). Программа преобразует измеряемые значения в нормированный показатель качества Q(X), проводит оперативный контроль состояния процесса и статистический анализ выборки.

### Входные данные:
*   Параметр X: скорость перемешивания, измеряется в об/мин.
*   Диапазон X: от 100 до 900 об/мин.
*   Количество измерений в выборке: N = 70.

### Формула преобразования Q(X):
Q(X) = 
*   2*(X - 350) + 5, при X < 350
*   0.5*(X - 500)^2 + 45, при 350 <= X <= 650
*   2*ln(X - 650 + 2) + 60, при X > 650

### Ручной расчет (Примеры):
1. X = 300 (меньше 350): Q = 2*(300 - 350) + 5 = -100 + 5 = -95.00
2. X = 500 (в диапазоне 350-650): Q = 0.5*(500 - 500)^2 + 45 = 45.00
3. X = 700 (больше 650): Q = 2*ln(700 - 650 + 2) + 60 = 2*ln(52) + 60 ≈ 2*3.951 + 60 ≈ 67.90

Выбор структуры данных для хранения характеристик технологического процесса имеет свои преимущества и обоснования:<mxfile host="app.diagrams.net">
  <diagram id="full" name="Блок-схема">
    <mxGraphModel dx="1241" dy="865" grid="1" gridSize="10" guides="1" tooltips="1" connect="1" arrows="1" fold="1" page="1" pageScale="1" pageWidth="827" pageHeight="1169" math="0" shadow="0">
      <root>
        <mxCell id="0" />
        <mxCell id="1" parent="0" />
        <mxCell id="b1" parent="1" style="rounded=1;arcSize=50;whiteSpace=wrap;html=1;fillColor=#ffffff;strokeColor=#000000;fontFamily=Times New Roman;fontSize=14;" value="Начало" vertex="1">
          <mxGeometry height="40" width="240" x="280" y="20" as="geometry" />
        </mxCell>
        <mxCell id="b2" parent="1" style="rounded=0;whiteSpace=wrap;html=1;fillColor=#ffffff;strokeColor=#000000;fontFamily=Times New Roman;fontSize=14;" value="setlocale(LC_ALL, &quot;Russian&quot;)" vertex="1">
          <mxGeometry height="50" width="240" x="280" y="100" as="geometry" />
        </mxCell>
        <mxCell id="b3" parent="1" style="shape=parallelogram;perimeter=parallelogramPerimeter;whiteSpace=wrap;html=1;fixedSize=1;fillColor=#ffffff;strokeColor=#000000;fontFamily=Times New Roman;fontSize=14;" value="Вывод: «Введите X:»" vertex="1">
          <mxGeometry height="50" width="240" x="280" y="190" as="geometry" />
        </mxCell>
        <mxCell id="b4" parent="1" style="shape=parallelogram;perimeter=parallelogramPerimeter;whiteSpace=wrap;html=1;fixedSize=1;fillColor=#ffffff;strokeColor=#000000;fontFamily=Times New Roman;fontSize=14;" value="Ввод X" vertex="1">
          <mxGeometry height="50" width="240" x="280" y="280" as="geometry" />
        </mxCell>
        <mxCell id="b5" parent="1" style="rhombus;whiteSpace=wrap;html=1;fillColor=#ffffff;strokeColor=#000000;fontFamily=Times New Roman;fontSize=14;" value="X &amp;lt; 350?" vertex="1">
          <mxGeometry height="80" width="180" x="310" y="370" as="geometry" />
        </mxCell>
        <mxCell id="b6" parent="1" style="rounded=0;whiteSpace=wrap;html=1;fillColor=#ffffff;strokeColor=#000000;fontFamily=Times New Roman;fontSize=14;" value="Q = 2 * (x - 350) + 5" vertex="1">
          <mxGeometry height="50" width="200" x="60" y="385" as="geometry" />
        </mxCell>
        <mxCell id="b7" parent="1" style="rhombus;whiteSpace=wrap;html=1;fillColor=#ffffff;strokeColor=#000000;fontFamily=Times New Roman;fontSize=14;" value="X ≤ 650?" vertex="1">
          <mxGeometry height="80" width="180" x="310" y="500" as="geometry" />
        </mxCell>
        <mxCell id="b8" parent="1" style="rounded=0;whiteSpace=wrap;html=1;fillColor=#ffffff;strokeColor=#000000;fontFamily=Times New Roman;fontSize=14;" value="Q = 0.5 * pow(x - 500, 2) + 45" vertex="1">
          <mxGeometry height="50" width="200" x="60" y="515" as="geometry" />
        </mxCell>
        <mxCell id="b9" parent="1" style="rounded=0;whiteSpace=wrap;html=1;fillColor=#ffffff;strokeColor=#000000;fontFamily=Times New Roman;fontSize=14;" value="&lt;font&gt;Q = 2*log(x-650*2)+60&lt;/font&gt;" vertex="1">
          <mxGeometry height="50" width="210" x="295" y="630" as="geometry" />
        </mxCell>
        <mxCell id="b10" parent="1" style="shape=parallelogram;perimeter=parallelogramPerimeter;whiteSpace=wrap;html=1;fixedSize=1;fillColor=#ffffff;strokeColor=#000000;fontFamily=Times New Roman;fontSize=14;" value="Вывод X, Q" vertex="1">
          <mxGeometry height="50" width="240" x="280" y="720" as="geometry" />
        </mxCell>
        <mxCell id="b11" parent="1" style="rounded=1;arcSize=50;whiteSpace=wrap;html=1;fillColor=#ffffff;strokeColor=#000000;fontFamily=Times New Roman;fontSize=14;" value="Конец" vertex="1">
          <mxGeometry height="40" width="240" x="280" y="810" as="geometry" />
        </mxCell>
        <mxCell id="e1" edge="1" parent="1" source="b1" style="edgeStyle=orthogonalEdgeStyle;rounded=0;html=1;endArrow=block;endFill=1;strokeColor=#000000;" target="b2">
          <mxGeometry relative="1" as="geometry" />
        </mxCell>
        <mxCell id="e2" edge="1" parent="1" source="b2" style="edgeStyle=orthogonalEdgeStyle;rounded=0;html=1;endArrow=block;endFill=1;strokeColor=#000000;" target="b3">
          <mxGeometry relative="1" as="geometry" />
        </mxCell>
        <mxCell id="e3" edge="1" parent="1" source="b3" style="edgeStyle=orthogonalEdgeStyle;rounded=0;html=1;endArrow=block;endFill=1;strokeColor=#000000;" target="b4">
          <mxGeometry relative="1" as="geometry" />
        </mxCell>
        <mxCell id="e4" edge="1" parent="1" source="b4" style="edgeStyle=orthogonalEdgeStyle;rounded=0;html=1;endArrow=block;endFill=1;strokeColor=#000000;" target="b5">
          <mxGeometry relative="1" as="geometry" />
        </mxCell>
        <mxCell id="e5" edge="1" parent="1" source="b5" style="edgeStyle=orthogonalEdgeStyle;rounded=0;html=1;endArrow=block;endFill=1;strokeColor=#000000;exitX=0;exitY=0.5;exitDx=0;exitDy=0;entryX=1;entryY=0.5;entryDx=0;entryDy=0;verticalAlign=bottom;fontFamily=Times New Roman;fontSize=12;" target="b6" value="&lt;font style=&quot;font-size: 14px;&quot;&gt;Да&lt;/font&gt;">
          <mxGeometry relative="1" as="geometry" />
        </mxCell>
        <mxCell id="e6" edge="1" parent="1" source="b5" style="edgeStyle=orthogonalEdgeStyle;rounded=0;html=1;endArrow=block;endFill=1;strokeColor=#000000;align=left;fontFamily=Times New Roman;fontSize=12;" target="b7" value="&lt;font style=&quot;font-size: 14px;&quot;&gt;Нет&lt;/font&gt;">
          <mxGeometry relative="1" as="geometry" />
        </mxCell>
        <mxCell id="e7" edge="1" parent="1" source="b7" style="edgeStyle=orthogonalEdgeStyle;rounded=0;html=1;endArrow=block;endFill=1;strokeColor=#000000;exitX=0;exitY=0.5;exitDx=0;exitDy=0;entryX=1;entryY=0.5;entryDx=0;entryDy=0;verticalAlign=bottom;fontFamily=Times New Roman;fontSize=12;" target="b8" value="&lt;font style=&quot;font-size: 14px;&quot;&gt;Да&lt;/font&gt;">
          <mxGeometry relative="1" as="geometry" />
        </mxCell>
        <mxCell id="e8" edge="1" parent="1" source="b7" style="edgeStyle=orthogonalEdgeStyle;rounded=0;html=1;endArrow=block;endFill=1;strokeColor=#000000;align=left;fontFamily=Times New Roman;fontSize=12;" target="b9" value="&lt;font style=&quot;font-size: 14px;&quot;&gt;Нет&lt;/font&gt;">
          <mxGeometry relative="1" as="geometry" />
        </mxCell>
        <mxCell id="e9" edge="1" parent="1" source="b9" style="edgeStyle=orthogonalEdgeStyle;rounded=0;html=1;endArrow=block;endFill=1;strokeColor=#000000;" target="b10">
          <mxGeometry relative="1" as="geometry" />
        </mxCell>
        <mxCell id="e10" edge="1" parent="1" source="b6" style="edgeStyle=orthogonalEdgeStyle;rounded=0;html=1;endArrow=block;endFill=1;strokeColor=#000000;exitX=0;exitY=0.5;exitDx=0;exitDy=0;entryX=0;entryY=0.5;entryDx=0;entryDy=0;" target="b10">
          <mxGeometry relative="1" as="geometry">
            <Array as="points">
              <mxPoint x="30" y="410" />
              <mxPoint x="30" y="745" />
            </Array>
          </mxGeometry>
        </mxCell>
        <mxCell id="e11" edge="1" parent="1" source="b8" style="edgeStyle=orthogonalEdgeStyle;rounded=0;html=1;endArrow=none;strokeColor=#000000;exitX=0;exitY=0.5;exitDx=0;exitDy=0;">
          <mxGeometry relative="1" as="geometry">
            <mxPoint x="30" y="540" as="targetPoint" />
          </mxGeometry>
        </mxCell>
        <mxCell id="e12" edge="1" parent="1" source="b10" style="edgeStyle=orthogonalEdgeStyle;rounded=0;html=1;endArrow=block;endFill=1;strokeColor=#000000;" target="b11">
          <mxGeometry relative="1" as="geometry" />
        </mxCell>
      </root>
    </mxGraphModel>
  </diagram>
</mxfile>

	1) Использование структуры позволяет объединить все характеристики процесса в одном объекте. Это делает код более организованным и удобочитаемым.
	2) Параметры скорость перемешивания и единица измерения позволяют задать контролируемую величину и её размерность. Это полезно для корректной интерпретации данных и вывода результатов.
	3) Параметры штатного режима хранят границы нормального функционирования реактора. Это позволяет легко определять отклонения от технологического регламента.
	4) Параметры базовое значение Q₀ и допустимый диапазон содержат информацию для оперативного контроля. Это полезно для расчёта границ LCL и UCL и сигнализации о нарушениях.
	5) Поля измерений и результатов преобразования представляют собой массивы значений X и Q. Это позволяет хранить информацию о каждом измерении отдельно, а также легко манипулировать ими при статистической обработке.
	6) Поля статистических характеристик содержат вычисленные показатели выборки. Это позволяет хранить результаты анализа и выводить их пользователю.

Комбинация всех этих параметров в структуре позволяет удобно хранить и работать с характеристиками технологического процесса. Она предоставляет удобный и организованный способ доступа к информации о процессе, а также позволяет легко изменять или расширять функциональность программы, связанную с мониторингом.
	<img width="573" height="898" alt="image" src="https://github.com/user-attachments/assets/991e3340-7285-43e1-b864-916a97bd6fb6" />

Цель работы: разработать систему мониторинга технологического процесса по параметру «скорость перемешивания» на основе преобразования измеряемой величины, оперативного контроля и статистического анализа.
Задачи проекта:
	Реализовать преобразование показания датчика X в нормированный показатель качества Q(X) в соответствии с заданной кусочно-нелинейной функцией.
	Провести оперативный контроль значений Q с использованием двойной границы относительно базового значения Q₀.
	Выполнить статистический анализ выборки значений Q на заданном интервале индексов.
	Выполнить дополнительное задание (индивидуализированное).
	Проверить корректность реализации на контрольном примере.


