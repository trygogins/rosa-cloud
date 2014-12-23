## Программа подключения облаков для [Росы](http://www.rosalab.ru/products/desktop)
Задача данной программы – предоставление удобного единообразного интерфейса для подключения облачных сервисов. Список поддерживаемых провайдеров находится в конце файла. 


### Добавление новых [WebDAV](http://en.wikipedia.org/wiki/WebDAV) провайдеров

Для добавления нового провайдера необходимо изменить конфигурационный файл [src/app/config.js](src/app/config.js). В массив ```providers``` добавляется новый объект с полями:
* ```name```: идентификатор провайдера
* ```title```: название, которое видит пользователь
* ```url```: адрес, по которому будет происходить подключение к сервису

### Добавление провайдров, имеющих клиент

Для добавления новых провайдеров, при подключении которых требуется установка клиента, придется лезть в исходники. В  [src/app/mainwindow.cpp](src/app/mainwindow.cpp) есть функция ```createSettingsButton```, которая содержит блоки ```if``` для определнеия типа провайдера. Как видно, в ней происходит связка со слотом, который отвечает за подключение провайдера (пример такого слота – ```installDropbox```). 

Дополнительно к изменениям исходников надо добавить элемент в конфиг [src/app/config.js](src/app/config.js). В массив ```providers``` добавляется новый объект с полями:
* ```name```: идентификатор провайдера
* ```title```: название, которое видит пользователь
* ```url```: пустая строка
* ```hasClient```: ```true```

### Список поддерживаемых провайдеров
* WebDAV  
  * [Яндекс.Диск](https://disk.yandex.ru)  
  * [Egnyte](http://www.egnyte.com/)
  * [4Shared](http://www.4shared.com/)
* Клиенты
  * [SpiderOak](https://spideroak.com)
  * [Dropbox](https://www.dropbox.com)
