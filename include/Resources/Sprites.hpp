#pragma once
#include <iostream>

namespace SliceDetails::Sprites{
    static std::string bloq = "iVBORw0KGgoAAAANSUhEUgAAAQAAAAEACAYAAABccqhmAAAACXBIWXMAAAsTAAALEwEAmpwYAAAFyGlUWHRYTUw6Y29tLmFkb2JlLnhtcAAAAAAAPD94cGFja2V0IGJlZ2luPSLvu78iIGlkPSJXNU0wTXBDZWhpSHpyZVN6TlRjemtjOWQiPz4gPHg6eG1wbWV0YSB4bWxuczp4PSJhZG9iZTpuczptZXRhLyIgeDp4bXB0az0iQWRvYmUgWE1QIENvcmUgNi4wLWMwMDYgNzkuMTY0NjQ4LCAyMDIxLzAxLzEyLTE1OjUyOjI5ICAgICAgICAiPiA8cmRmOlJERiB4bWxuczpyZGY9Imh0dHA6Ly93d3cudzMub3JnLzE5OTkvMDIvMjItcmRmLXN5bnRheC1ucyMiPiA8cmRmOkRlc2NyaXB0aW9uIHJkZjphYm91dD0iIiB4bWxuczp4bXA9Imh0dHA6Ly9ucy5hZG9iZS5jb20veGFwLzEuMC8iIHhtbG5zOnhtcE1NPSJodHRwOi8vbnMuYWRvYmUuY29tL3hhcC8xLjAvbW0vIiB4bWxuczpzdEV2dD0iaHR0cDovL25zLmFkb2JlLmNvbS94YXAvMS4wL3NUeXBlL1Jlc291cmNlRXZlbnQjIiB4bWxuczpkYz0iaHR0cDovL3B1cmwub3JnL2RjL2VsZW1lbnRzLzEuMS8iIHhtbG5zOnBob3Rvc2hvcD0iaHR0cDovL25zLmFkb2JlLmNvbS9waG90b3Nob3AvMS4wLyIgeG1wOkNyZWF0b3JUb29sPSJBZG9iZSBQaG90b3Nob3AgMjIuMiAoV2luZG93cykiIHhtcDpDcmVhdGVEYXRlPSIyMDIxLTA3LTIzVDIzOjI3OjM0LTA3OjAwIiB4bXA6TWV0YWRhdGFEYXRlPSIyMDIxLTA3LTIzVDIzOjI3OjM0LTA3OjAwIiB4bXA6TW9kaWZ5RGF0ZT0iMjAyMS0wNy0yM1QyMzoyNzozNC0wNzowMCIgeG1wTU06SW5zdGFuY2VJRD0ieG1wLmlpZDozNjg2M2ViYy0wMzY0LWU0NDAtYTBhMi1hNGMzYmM5OTg2N2QiIHhtcE1NOkRvY3VtZW50SUQ9ImFkb2JlOmRvY2lkOnBob3Rvc2hvcDo2ZGY5NjE2MS04YzdiLWIxNDMtOTE2ZC1l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";
    static std::string bloq_arrow = "iVBORw0KGgoAAAANSUhEUgAAAQAAAAEACAYAAABccqhmAAAACXBIWXMAAAsTAAALEwEAmpwYAAAGvmlUWHRYTUw6Y29tLmFkb2JlLnhtcAAAAAAAPD94cGFja2V0IGJlZ2luPSLvu78iIGlkPSJXNU0wTXBDZWhpSHpyZVN6TlRjemtjOWQiPz4gPHg6eG1wbWV0YSB4bWxuczp4PSJhZG9iZTpuczptZXRhLyIgeDp4bXB0az0iQWRvYmUgWE1QIENvcmUgNi4wLWMwMDYgNzkuMTY0NjQ4LCAyMDIxLzAxLzEyLTE1OjUyOjI5ICAgICAgICAiPiA8cmRmOlJERiB4bWxuczpyZGY9Imh0dHA6Ly93d3cudzMub3JnLzE5OTkvMDIvMjItcmRmLXN5bnRheC1ucyMiPiA8cmRmOkRlc2NyaXB0aW9uIHJkZjphYm91dD0iIiB4bWxuczp4bXA9Imh0dHA6Ly9ucy5hZG9iZS5jb20veGFwLzEuMC8iIHhtbG5zOnhtcE1NPSJodHRwOi8vbnMuYWRvYmUuY29tL3hhcC8xLjAvbW0vIiB4bWxuczpzdEV2dD0iaHR0cDovL25zLmFkb2JlLmNvbS94YXAvMS4wL3NUeXBlL1Jlc291cmNlRXZlbnQjIiB4bWxuczpkYz0iaHR0cDovL3B1cmwub3JnL2RjL2VsZW1lbnRzLzEuMS8iIHhtbG5zOnBob3Rvc2hvcD0iaHR0cDovL25zLmFkb2JlLmNvbS9waG90b3Nob3AvMS4wLyIgeG1wOkNyZWF0b3JUb29sPSJBZG9iZSBQaG90b3Nob3AgMjIuMiAoV2luZG93cykiIHhtcDpDcmVhdGVEYXRlPSIyMDIxLTA3LTIzVDIzOjI3OjIyLTA3OjAwIiB4bXA6TWV0YWRhdGFEYXRlPSIyMDIxLTA4LTAzVDE4OjQ5OjI0LTA3OjAwIiB4bXA6TW9kaWZ5RGF0ZT0iMjAyMS0wOC0wM1QxODo0OToyNC0wNzowMCIgeG1wTU06SW5zdGFuY2VJRD0ieG1wLmlpZDo5M2YxMjhiOC0xNTMwLWEwNDctOWU2MC1mNzY2ZDYzY2Y0YWEiIHhtcE1NOkRvY3VtZW50SUQ9ImFkb2JlOmRvY2lkOnBob3Rvc2hvcDo1MGJjNmI1OC1mMWYwLTgzNGUtOWI0NS04Mjc2MmIzMzUzODUiIHhtcE1NOk9yaWdpbmFsRG9jdW1lbnRJRD0ieG1wLmRpZDplZmE0YzhhZS1kZjBkLTNlNGUtYjJlMS01ZDhmYTQ1MTA4ZTIiIGRjOmZvcm1hdD0iaW1hZ2UvcG5nIiBwaG90b3Nob3A6Q29sb3JNb2RlPSIzIiBwaG90b3Nob3A6SUNDUHJvZmlsZT0ic1JHQiBJRUM2MTk2Ni0yLjEiPiA8eG1wTU06SGlzdG9yeT4gPHJkZjpTZXE+IDxyZGY6bGkgc3RFdnQ6YWN0aW9uPSJjcmVhdGVkIiBzdEV2dDppbnN0YW5jZUlEPSJ4bXAuaWlkOmVmYTRjOGFlLWRmMGQtM2U0ZS1iMmUxLTVkOGZhNDUxMDhlMiIgc3RFdnQ6d2hlbj0iMjAyMS0wNy0yM1QyMzoyNzoyMi0wNzowMCIgc3RFdnQ6c29mdHdhcmVBZ2VudD0iQWRvYmUgUGhvdG9zaG9wIDIyLjIgKFdpbmRvd3MpIi8+IDxyZGY6bGkgc3RFdnQ6YWN0aW9uPSJzYXZlZCIgc3RFdnQ6aW5zdGFuY2VJRD0ieG1wLmlpZDo0ZjU4NzZiOS1lMjRjLTQyNGUtYmY5Zi05NmQxOGRmZjdmNTIiIHN0RXZ0OndoZW49IjIwMjEtMDctMjNUMjM6Mjc6MjItMDc6MDAiIHN0RXZ0OnNvZnR3YXJlQWdlbnQ9IkFkb2JlIFBob3Rvc2hvcCAyMi4yIChXaW5kb3dzKSIgc3RFdnQ6Y2hhbmdlZD0iLyIvPiA8cmRmOmxpIHN0RXZ0OmFjdGlvbj0ic2F2ZWQiIHN0RXZ0Omluc3RhbmNlSUQ9InhtcC5paWQ6OTNmMTI4YjgtMTUzMC1hMDQ3LTllNjAtZjc2NmQ2M2NmNGFhIiBzdEV2dDp3aGVuPSIyMDIxLTA4LTAzVDE4OjQ5OjI0LTA3OjAwIiBzdEV2dDpzb2Z0d2FyZUFnZW50PSJBZG9iZSBQaG90b3Nob3AgMjIuMiAoV2luZG93cykiIHN0RXZ0OmNoYW5nZWQ9Ii8iLz4gPC9yZGY6U2VxPiA8L3htcE1NOkhpc3Rvcnk+IDwvcmRmOkRlc2NyaXB0aW9uPiA8L3JkZjpSREY+IDwveDp4bXBtZXRhPiA8P3hwYWNrZXQgZW5kPSJyIj8+jhW7uAAACIhJREFU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";
    static std::string cut_arrow = "iVBORw0KGgoAAAANSUhEUgAAAQAAAAEACAYAAABccqhmAAAACXBIWXMAAAsTAAALEwEAmpwYAAAGvmlUWHRYTUw6Y29tLmFkb2JlLnhtcAAAAAAAPD94cGFja2V0IGJlZ2luPSLvu78iIGlkPSJXNU0wTXBDZWhpSHpyZVN6TlRjemtjOWQiPz4gPHg6eG1wbWV0YSB4bWxuczp4PSJhZG9iZTpuczptZXRhLyIgeDp4bXB0az0iQWRvYmUgWE1QIENvcmUgNi4wLWMwMDYgNzkuMTY0NjQ4LCAyMDIxLzAxLzEyLTE1OjUyOjI5ICAgICAgICAiPiA8cmRmOlJERiB4bWxuczpyZGY9Imh0dHA6Ly93d3cudzMub3JnLzE5OTkvMDIvMjItcmRmLXN5bnRheC1ucyMiPiA8cmRmOkRlc2NyaXB0aW9uIHJkZjphYm91dD0iIiB4bWxuczp4bXA9Imh0dHA6Ly9ucy5hZG9iZS5jb20veGFwLzEuMC8iIHhtbG5zOnhtcE1NPSJodHRwOi8vbnMuYWRvYmUuY29tL3hhcC8xLjAvbW0vIiB4bWxuczpzdEV2dD0iaHR0cDovL25zLmFkb2JlLmNvbS94YXAvMS4wL3NUeXBlL1Jlc291cmNlRXZlbnQjIiB4bWxuczpkYz0iaHR0cDovL3B1cmwub3JnL2RjL2VsZW1lbnRzLzEuMS8iIHhtbG5zOnBob3Rvc2hvcD0iaHR0cDovL25zLmFkb2JlLmNvbS9waG90b3Nob3AvMS4wLyIgeG1wOkNyZWF0b3JUb29sPSJBZG9iZSBQaG90b3Nob3AgMjIuMiAoV2luZG93cykiIHhtcDpDcmVhdGVEYXRlPSIyMDIxLTA3LTI0VDAyOjQ1OjQyLTA3OjAwIiB4bXA6TWV0YWRhdGFEYXRlPSIyMDIxLTA4LTA0VDEzOjU1OjAxLTA3OjAwIiB4bXA6TW9kaWZ5RGF0ZT0iMjAyMS0wOC0wNFQxMzo1NTowMS0wNzowMCIgeG1wTU06SW5zdGFuY2VJRD0ieG1wLmlpZDo0MjI0M2FjZi01YTZkLTM5NDktYWQ2Yi0yOWVjNDkwZmYwZjMiIHhtcE1NOkRvY3VtZW50SUQ9ImFkb2JlOmRvY2lkOnBob3Rvc2hvcDpjOTQzMzI5MS1kZDM5LTFmNDAtYmZhMi1iMjQzNTMxNWExNTAiIHhtcE1NOk9yaWdpbmFsRG9jdW1lbnRJRD0ieG1wLmRpZDowMzc5OGNhNS0zMzQ3LWMwNGItYWViOC1iNzhlNGNiYWEzMTkiIGRjOmZvcm1hdD0iaW1hZ2UvcG5nIiBwaG90b3Nob3A6Q29sb3JNb2RlPSIzIiBwaG90b3Nob3A6SUNDUHJvZmlsZT0ic1JHQiBJRUM2MTk2Ni0yLjEiPiA8eG1wTU06SGlzdG9yeT4gPHJkZjpTZXE+IDxyZGY6bGkgc3RFdnQ6YWN0aW9uPSJjcmVhdGVkIiBzdEV2dDppbnN0YW5jZUlEPSJ4bXAuaWlkOjAzNzk4Y2E1LTMzNDctYzA0Yi1hZWI4LWI3OGU0Y2JhYTMxOSIgc3RFdnQ6d2hlbj0iMjAyMS0wNy0yNFQwMjo0NTo0Mi0wNzowMCIgc3RFdnQ6c29mdHdhcmVBZ2VudD0iQWRvYmUgUGhvdG9zaG9wIDIyLjIgKFdpbmRvd3MpIi8+IDxyZGY6bGkgc3RFdnQ6YWN0aW9uPSJzYXZlZCIgc3RFdnQ6aW5zdGFuY2VJRD0ieG1wLmlpZDo4NTVlZmZmNC01YjUxLTM3NGQtOTVhMC0xZDdjOTQwZTQwMGYiIHN0RXZ0OndoZW49IjIwMjEtMDctMjRUMDI6NDU6NDItMDc6MDAiIHN0RXZ0OnNvZnR3YXJlQWdlbnQ9IkFkb2JlIFBob3Rvc2hvcCAyMi4yIChXaW5kb3dzKSIgc3RFdnQ6Y2hhbmdlZD0iLyIvPiA8cmRmOmxpIHN0RXZ0OmFjdGlvbj0ic2F2ZWQiIHN0RXZ0Omluc3RhbmNlSUQ9InhtcC5paWQ6NDIyNDNhY2YtNWE2ZC0zOTQ5LWFkNmItMjllYzQ5MGZmMGYzIiBzdEV2dDp3aGVuPSIyMDIxLTA4LTA0VDEzOjU1OjAxLTA3OjAwIiBzdEV2dDpzb2Z0d2FyZUFnZW50PSJBZG9iZSBQaG90b3Nob3AgMjIuMiAoV2luZG93cykiIHN0RXZ0OmNoYW5nZWQ9Ii8iLz4gPC9yZGY6U2VxPiA8L3htcE1NOkhpc3Rvcnk+IDwvcmRmOkRlc2NyaXB0aW9uPiA8L3JkZjpSREY+IDwveDp4bXBtZXRhPiA8P3hwYWNrZXQgZW5kPSJyIj8+hbgEqgAABVtJREFUeJzt3U2KZ1cBh+FfSwwIkghqlCgZZihkIw5dgYoLMDtwFwppP0jIKFEHigNXoAZ0EnWqAQOCUxulMugqCG3squ76V3Xlvs8DBU19nHuhuG+dc8+Bvnd2djZSLvuF37uVu+BO+MyzvgHg2REACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBMACBOAY/jutudu8XrPbfv2LV6PGyIAx/D5bb/Z9tVbuNbXtv122+du4VrcsHtnZ2fP+h64vpe2/X3bP7d9b9u7j/ney37h9x7ztW9u+9G2F7e9fH49PsXMAI7hw22/2vaVbe9se3vbKycc/5XzMX++7cvbfjkP/yEIwHG88bF/f2vb+9t+sO2Fa4z5wvkY75+PeeHH1xiTO8QS4Die3/bBti8+8vl/bfvh+cdfd7UlwKvbvnP+8eIjX//Htq9v+8/1bpe7wAzgOB5se/MTPv+Fba9v+8u2311hnD9s+/O27+9/H/5t+9k8/IdhBnAsr+3hA3yTvrHtTzd8DW6JGcCxvLebfTh/f8Pjc8sE4Hju3+DYXv4djCXA8VycCTj1ycAHs/d/OGYAx3NxJuDU7P0fkAAc0xuXf8sTM/0/IEuAY3p+D5cBXzrRePb+D8oM4JgebHvrhOPZ+z8oATiuUy4DTP8PSgCO671tfzzBOPb+D0wAju0Uf7n99T8wLwGP7aVtf9v22af8eXv/B2cGcGwfbvv1NX7e3v/BCcDxXedloOn/wVkCHN/Tngmw9x9gBnB8T3sm4Kfz8B+eADQ8zTLgJye/C+4cAWh40jMB9v4jBKDjSV7o3b+pm+Bu8RKw46pnAuz9h5gBdFz1TMAv5uHPEICWq7wM9PIvxBKg5bIzAfb+Y8wAWi47E2DvP0YAeh63DDD9jxGAnv93JsDef5AANH3SmYD7t30TPHteAjY9eibA3n+UGUDTo2cC7P1HCUDXx18GevkXZQnQdXEm4L+z95916v8/jk+PizMB/56HP8sMoO21PXz4bf9FfQQMOZ47uzMqOgAAAABJRU5ErkJggg==";
    static std::string dot = "iVBORw0KGgoAAAANSUhEUgAAAQAAAAEACAYAAABccqhmAAAACXBIWXMAAAsTAAALEwEAmpwYAAAFuWlUWHRYTUw6Y29tLmFkb2JlLnhtcAAAAAAAPD94cGFja2V0IGJlZ2luPSLvu78iIGlkPSJXNU0wTXBDZWhpSHpyZVN6TlRjemtjOWQiPz4gPHg6eG1wbWV0YSB4bWxuczp4PSJhZG9iZTpuczptZXRhLyIgeDp4bXB0az0iQWRvYmUgWE1QIENvcmUgNi4wLWMwMDYgNzkuMTY0NjQ4LCAyMDIxLzAxLzEyLTE1OjUyOjI5ICAgICAgICAiPiA8cmRmOlJERiB4bWxuczpyZGY9Imh0dHA6Ly93d3cudzMub3JnLzE5OTkvMDIvMjItcmRmLXN5bnRheC1ucyMiPiA8cmRmOkRlc2NyaXB0aW9uIHJkZjphYm91dD0iIiB4bWxuczp4bXA9Imh0dHA6Ly9ucy5hZG9iZS5jb20veGFwLzEuMC8iIHhtbG5zOnhtcE1NPSJodHRwOi8vbnMuYWRvYmUuY29tL3hhcC8xLjAvbW0vIiB4bWxuczpzdEV2dD0iaHR0cDovL25zLmFkb2JlLmNvbS94YXAvMS4wL3NUeXBlL1Jlc291cmNlRXZlbnQjIiB4bWxuczpkYz0iaHR0cDovL3B1cmwub3JnL2RjL2VsZW1lbnRzLzEuMS8iIHhtbG5zOnBob3Rvc2hvcD0iaHR0cDovL25zLmFkb2JlLmNvbS9waG90b3Nob3AvMS4wLyIgeG1wOkNyZWF0b3JUb29sPSJBZG9iZSBQaG90b3Nob3AgMjIuMiAoV2luZG93cykiIHhtcDpDcmVhdGVEYXRlPSIyMDIxLTA3LTIzVDIzOjI4LTA3OjAwIiB4bXA6TWV0YWRhdGFEYXRlPSIyMDIxLTA3LTIzVDIzOjI4LTA3OjAwIiB4bXA6TW9kaWZ5RGF0ZT0iMjAyMS0wNy0yM1QyMzoyOC0wNzowMCIgeG1wTU06SW5zdGFuY2VJRD0ieG1wLmlpZDplNzMzNDE2NC1hZjRlLWEwNDktOTUxNi0xZmFjNDU5N2Q3ZWIiIHhtcE1NOkRvY3VtZW50SUQ9ImFkb2JlOmRvY2lkOnBob3Rvc2hvcDoxMzM2MzE3Ni01ZTdiLTUwNDEtYTkwMi1jYjVlNTY2YjYz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";
}