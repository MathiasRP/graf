#include "CordinatSystem.hpp"

CordinatSystem::CordinatSystem(int height, int width, int x_offset, int y_offset, std::string x_name, std::string y_name)
{
    this->height = height;
    this->width = width;
    this->x_offset = x_offset;
    this->x_name.setString(x_name);
    
    this->y_offset = y_offset;
    this->y_name.setString(y_name);

    this->firstMark = 10;
    this->firstMarkValue = 10;
    this->pointInterval = 2;
}

CordinatSystem::~CordinatSystem()
{
    for(size_t i  =0; i < this->funtions.size(); i++){
        delete this->funtions[i].function;
    }
    
    this->funtions.clear();
}

void CordinatSystem::initialize(){
    setSize();
    setPos();
    
    this->x_line.setFillColor(sf::Color::Black);
    this->x_name.setCharacterSize(20);
    this->x_name.setFillColor(sf::Color::Black);
    this->x_name.setFont(this->font);

    this->y_line.setFillColor(sf::Color::Black);
    this->y_name.setCharacterSize(20);
    this->y_name.setFillColor(sf::Color::Black);
    this->y_name.setFont(this->font);

    this->background.setFillColor(sf::Color::White);
}

void CordinatSystem::setBackgroundColor(sf::Color& color){
    this->background.setFillColor(color);
}

void CordinatSystem::setSize(int height, int width){
    this->height = height;
    this->width = width;

    setSize();
    setPos();
    resetAllFuntions();
}

void CordinatSystem::setPosition(sf::Vector2i& pos){
    this->position = pos;

    setSize();
    setPos();
    resetAllFuntions();
}

void CordinatSystem::setPosition(int x, int y){
    this->position.x = x;
    this->position.y = y;

    setSize();
    setPos();
    resetAllFuntions();
}

bool CordinatSystem::setFont(std::string filePath){
        
    fontLoaded = font.loadFromFile(filePath);
    return fontLoaded;
}

void CordinatSystem::setFontSize(int size){
    this->x_name.setCharacterSize(size);
    this->y_name.setCharacterSize(size);

    for(size_t i = 0; i < this->funtions.size(); i++){
        this->funtions[i].nameText.setCharacterSize(size);
    }

    setTextPos();
}

void CordinatSystem::setSize(){
    this->x_line.setSize(sf::Vector2f(this->width, 1));
    this->y_line.setSize(sf::Vector2f(1, this->height));   

    this->background.setSize(sf::Vector2f(this->width, this->height));
}

void CordinatSystem::setPos(){
    this->x_line.setPosition(sf::Vector2f(this->position.x, this->position.y + this->height - this->y_offset));
    this->y_line.setPosition(sf::Vector2f(this->position.x + this->y_offset, this->position.y));

    this->background.setPosition(sf::Vector2f(this->position.x, this->position.y));

    setTextPos();
    reloadMarks();
}

void CordinatSystem::move(sf::Vector2f& vector){
    this->position.x += vector.x;
    this->position.y += vector.y;

    resetAllFuntions();
}

void CordinatSystem::setFirstMark(int pixel){
    this->firstMark = pixel;

    resetAllFuntions();
    reloadMarks();
}

void CordinatSystem::setShowMarks(bool show){
    this->showMarks = show;

    //resetAllFuntions();
    reloadMarks();
}

void CordinatSystem::setFirstMarkValue(int value){
    this->firstMarkValue = value;

    resetAllFuntions();
}

void CordinatSystem::setPointInterval(int interval){
    this->pointInterval = interval;

    resetAllFuntions();
}

void CordinatSystem::setTextPos(){
    int length = 0;
    if(this->x_name.getString().getSize() > 0){
        length = (this->x_name.getCharacterSize() * this->x_name.getString().getSize()) / 2;
        if(x_offset - this->x_name.getCharacterSize() > 0){
            this->x_name.setPosition(this->width - length - 5, this->height - x_offset + 1);
        }else{
            this->x_name.setPosition(this->width - length - 5, this->height - x_offset - this->x_name.getCharacterSize() - 1);
        }
    }

    if(this->y_name.getString().getSize() > 0){
        this->y_name.setPosition(this->position.x + y_offset + 5, this->position.y + 5);
    }

    for(size_t i = 0; i < this->funtions.size(); i++){
        sf::Vertex& last = this->funtions[i].verticies[this->funtions[i].verticies.getVertexCount() - 1];
        size_t lenght = this->funtions[i].nameText.getString().getSize() * this->funtions[i].nameText.getCharacterSize();
        sf::Vector2f textPos;
        textPos.y = last.position.y;
    
        if(last.position.x + lenght + 5 > this->position.x + width){
            textPos.x = (this->position.x + width + 5) - lenght;
        }else{
            textPos.x = last.position.x;
        }
        this->funtions[i].nameText.setPosition(textPos);
    }
}

void CordinatSystem::setX_Name(std::string name){
    this->x_name.setString(name);
    setTextPos();
}

void CordinatSystem::setX_Offset(int offset){
    this->x_offset = offset;
    setPos();
}

void CordinatSystem::setX_Color(sf::Color color){
    this->x_line.setFillColor(color);
}

void CordinatSystem::setY_Name(std::string name){
    this->y_name.setString(name);
    setTextPos();
}

void CordinatSystem::setY_Offset(int offset){
    this->y_offset = offset;
    setPos();
}

void CordinatSystem::setY_Color(sf::Color color){
    this->y_line.setFillColor(color);
}

void CordinatSystem::addFunction(MathFunction* func, std::string name){
    this->funtions.push_back(FunctionElements());
    FunctionElements& functionElm = this->funtions[this->funtions.size() -1];
    functionElm.function = func->clone();
    functionElm.nameText.setString(name);
    functionElm.nameText.setFont(font);
    functionElm.nameText.setFillColor(func->color);
    functionElm.nameText.setCharacterSize(this->x_name.getCharacterSize());

    functionElm.verticies.setPrimitiveType(sf::LinesStrip);
    
    //TODO: test/create vertisie;
    setFunction(this->funtions.size() - 1);
}

void CordinatSystem::removeFuntion(int index){
    delete this->funtions[index].function;

    this->funtions.erase(this->funtions.begin() + index);
}

size_t CordinatSystem::countFuntions(){
    return this->funtions.size();
}

MathFunction* CordinatSystem::operator[](int index){
    return  this->funtions[index].function;
}

void CordinatSystem::reloadMarks(){
    this->marks.clear();

    if(showMarks){
        int current = y_offset - firstMark;
        while(current > 0){
            current -= firstMark;
        }
        current += firstMark;

        while (current < width)//Y Line
        {
            if(current != y_offset){
                marks.push_back(sf::RectangleShape());
                sf::RectangleShape& newRect = marks[marks.size() - 1];
                newRect.setSize(sf::Vector2f(1, 10));
                newRect.setPosition(current, height - x_offset - 5);
            }
            current += firstMark;
        }
        
        current = x_offset + firstMark;
        while(current < height){
            current += firstMark;
        }
        current -= firstMark;

        while (current > 0)//X Line
        {
            if(current != height - x_offset){
                marks.push_back(sf::RectangleShape());
                sf::RectangleShape& newRect = marks[marks.size() - 1];
                newRect.setSize(sf::Vector2f(10, 1));
                newRect.setPosition(y_offset - 5, current);
            }
            current -= firstMark;
        }
    }
}

void CordinatSystem::resetAllFuntions(){
    for(size_t i = 0; i < this->funtions.size(); i++){
        setFunction(i);
    }
}

void CordinatSystem::setFunction(int index){
    this->funtions[index].verticies.clear();
    double markDiff = (double)firstMarkValue / (double)firstMark;
    sf::Vector2f point;
    for(int x = 0; x < width; x += this->pointInterval){
        //firstMarkValue
        //firstMark
        //firstmarkValue / firstMark => double
        int y = this->funtions[index].function->getY((x - x_offset) * markDiff) + y_offset;

        point.x = this->position.x + x;
        point.y = this->position.y + height - y;
        if(point.y < height && point.y > position.y){
            sf::Vertex v(point);
            v.color = this->funtions[index].function->color;
            this->funtions[index].verticies.append(v);
        }
    }

    sf::Vertex& last = this->funtions[index].verticies[this->funtions[index].verticies.getVertexCount() - 1];
    size_t lenght = this->funtions[index].nameText.getString().getSize() * this->funtions[index].nameText.getCharacterSize();
    sf::Vector2f textPos;
    textPos.y = last.position.y;
    
    if(last.position.x + lenght + 5 > this->position.x + width){
        textPos.x = (this->position.x + width + 5) - lenght;
    }else{
        textPos.x = last.position.x;
    }
    this->funtions[index].nameText.setPosition(textPos);
}

void CordinatSystem::update(){

}

void CordinatSystem::draw(sf::RenderTarget& target) {
    target.draw(background);

    target.draw(y_line);
    target.draw(x_line);

    for (size_t i = 0; i < funtions.size(); i++) {
        target.draw(funtions[i].verticies);
        if (fontLoaded) {
            target.draw(funtions[i].nameText);
        }
    }

    if (fontLoaded && this->x_name.getString().getSize() > 0) {
        x_name.setFillColor(sf::Color::Black); // Set the text color to black
        target.draw(x_name);
    }

    if (fontLoaded && this->y_name.getString().getSize() > 0) {
        y_name.setFillColor(sf::Color::Black); // Set the text color to black
        target.draw(y_name);
    }

    for (int i = 0; i < marks.size(); i++) {
        marks[i].setFillColor(sf::Color::Black); // Set the line color to black
        target.draw(marks[i]);
    }
}
