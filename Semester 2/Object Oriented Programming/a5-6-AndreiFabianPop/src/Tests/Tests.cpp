//
// Created by andre on 21/03/2022.
//

#include "Tests.h"

void Tests::testDomain()
{
    Tutorial tutorial;

    assert(tutorial.get_title().empty());
    assert(tutorial.get_likes() == 0);

    tutorial.set_title("Title");
    assert(tutorial.get_title() == "Title");

    tutorial.set_presenter("Pres");
    assert(tutorial.get_presenter() == "Pres");

    tutorial.set_duration_minutes(11);
    assert(tutorial.get_duration_minutes() == 11);

    tutorial.set_duration_seconds(11);
    assert(tutorial.get_duration_seconds() == 11);

    tutorial.set_likes(55);
    assert(tutorial.get_likes() == 55);

    tutorial.set_link("link");
    assert(tutorial.get_link() == "link");

    Tutorial tutorial1 = tutorial;
}

void Tests::testRepository() {
    Repository<Tutorial> dynamicVector;
    Repository<Tutorial> dynamicVector1(dynamicVector);
    Repository<Tutorial> dynamicVector2 = dynamicVector1;
    dynamicVector = dynamicVector;

    int res1 = dynamicVector1.add(Tutorial("title", "pres", 1, 1, 1, "www"));
    assert(res1 == 1);
    int res2 = dynamicVector1.add(Tutorial("title", "pres", 1, 1, 1, "www"));
    assert(res2 == 0);
    assert(dynamicVector1[0].get_title() == "title");

    assert(dynamicVector1.getSize() == 1);

    dynamicVector1.add(Tutorial("title2", "pres", 1, 1, 1, "www"));
    assert(dynamicVector1.getSize() == 2);

    dynamicVector1.remove(0);
    assert(dynamicVector1.getSize() == 1);
    assert(dynamicVector1[0].get_title() == "title2");

    dynamicVector1.add(Tutorial("title", "pres", 1, 1, 1, "www"));
    assert(dynamicVector1.get_index("title", "pres", "www") == 1);
    assert(dynamicVector1.get_index("element", "no", "existent") == -1);

    assert(dynamicVector1.valid_index(1) == true);
    assert(dynamicVector1.valid_index(7) == false);

    dynamicVector1.add(Tutorial("title3", "pres", 1, 1, 1, "www"));
    Repository<Tutorial> dynamicVector3 = dynamicVector1;

    dynamicVector1 + Tutorial("title3", "pres", 1, 1, 1, "www");
    dynamicVector1 + Tutorial("title5", "pres", 1, 1, 1, "www");
    assert(dynamicVector1[2].get_title() == "title3");
}

void Tests::testService() {
    Repository<Tutorial> dynamicVector;
    Service service(dynamicVector);

    int res = service.add("title", "pres", -1, 0, 0, "www");
    assert(res == -1);

    res = service.add("title", "pres", 0, 61, 0, "www");
    assert(res == -2);

    res = service.add("title", "pres", 1, 0, -1, "www");
    assert(res == -3);

    res = service.add("title", "pres", 1, 0, 0, "www");
    assert(res == 1);

    int res2 = service.remove(-1);
    assert(res2 == 0);

    res2 = service.remove(0);
    assert(res2 == 1);

    service.add("tt", "pp", 0, 0, 0, "ll");

    Repository<Tutorial> dynamicVector1 = service.get_all();
    assert(dynamicVector1[0].get_title() == service.get_all()[0].get_title());

    int re = service.add("title", "pres", 1, 0, 0, "www");
    service.update(0, 0, "new", -1);
    assert(service.get_all()[0].get_title() == "new");
    service.get_by_presenter("");
    service.add_to_playlist(Tutorial("title3", "pres", 1, 1, 1, "www"));
    service.get_by_presenter("pres");
    service.remove_from_playlist(0);
    service.get_watchList();

    service.update(0, 1, "newp", -1);
    assert(service.get_all()[0].get_presenter() == "newp");

    service.update(0, 2, "", 5);
    assert(service.get_all()[0].get_duration_minutes() == 5);

    service.update(0, 3, "", 5);
    assert(service.get_all()[0].get_duration_seconds() == 5);

    service.update(0, 4, "", 5);
    assert(service.get_all()[0].get_likes() == 5);

    service.update(0, 5, "link1", -1);
    assert(service.get_all()[0].get_link() == "link1");

    assert(service.valid_index(0) == true);
}
