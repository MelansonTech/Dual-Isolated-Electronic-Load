void SetPointMinMaxUpdate(void) {

  switch (LDA.Mode.range) {

    case 0: //CC Load

      switch (LDA.volt.range) {

        case 0: //HV Range

          LDA.CurrentMax = 0.35;
          LDA.CurrentMin = 0;

          break;

        case 1: //MV Range

          switch (LDA.current.range) {

            case 0: // LC Range

              LDA.CurrentMax = 0.35;
              LDA.CurrentMin = 0;

              break;

            case 1: // MC Range

              LDA.CurrentMax = 3;
              LDA.CurrentMin = 0;
              break;
          }
          break;

        case 2: //LV Range

          switch (LDA.current.range) {

            case 0: // LC Range

              LDA.CurrentMax = 0.35;
              LDA.CurrentMin = 0;

              break;

            case 1: // MC Range

              LDA.CurrentMax = 3;
              LDA.CurrentMin = 0;

              break;

            case 2:

              LDA.CurrentMax = 10;
              LDA.CurrentMin = 0;

              break;

          }

          break;
      }

      break;

    case 1: //CR Load

      switch (LDA.volt.range) {

        case 0: //HV Range

          LDA.CurrentMax = 5000;
          LDA.CurrentMin = 1150;

          break;

        case 1: //MV Range

          switch (LDA.current.range) {

            case 0: // LC Range

              LDA.CurrentMax = 1500;
              LDA.CurrentMin = 170;

              break;

            case 1: // MC Range

              LDA.CurrentMax = 150;
              LDA.CurrentMin = 20;

              break;

          }

          break;

        case 2: //LV Range

          switch (LDA.current.range) {
            case 0: // LC Range

              LDA.CurrentMax = 1000;
              LDA.CurrentMin = 60;
              break;

            case 1: // MC Range
              LDA.CurrentMax = 100;
              LDA.CurrentMin = 6.5;
              break;

            case 2:
              LDA.CurrentMax = 50;
              LDA.CurrentMin = 2;
              break;
          }
      }

      break;

    case 2: //CP Load

      LDA.CurrentMax = 200;
      LDA.CurrentMin = 0;

      break;

  }

  switch (LDB.Mode.range) {

    case 0: //CC Load
      switch (LDB.volt.range) {

        case 0: //HV Range

          LDB.CurrentMax = 0.35;
          LDB.CurrentMin = 0;

          break;

        case 1: //MV Range

          switch (LDB.current.range) {

            case 0: // LC Range

              LDB.CurrentMax = 0.35;
              LDB.CurrentMin = 0;

              break;

            case 1: // MC Range

              LDB.CurrentMax = 3;
              LDB.CurrentMin = 0;
              break;
          }
          break;

        case 2: //LV Range

          switch (LDB.current.range) {
            case 0: // LC Range

              LDB.CurrentMax = 0.35;
              LDB.CurrentMin = 0;
              break;

            case 1: // MC Range
              LDB.CurrentMax = 3;
              LDB.CurrentMin = 0;
              break;

            case 2:
              LDB.CurrentMax = 10;
              LDB.CurrentMin = 0;
              break;
          }

          break;
      }
      break;

    case 1: //CR Load

      switch (LDB.volt.range) {

        case 0: //HV Range

          LDB.CurrentMax = 5000;
          LDB.CurrentMin = 1150;

          break;

        case 1: //MV Range

          switch (LDB.current.range) {

            case 0: // LC Range

              LDB.CurrentMax = 1500;
              LDB.CurrentMin = 170;

              break;

            case 1: // MC Range

              LDB.CurrentMax = 150;
              LDB.CurrentMin = 20;

              break;

          }

          break;

        case 2: //LV Range

          switch (LDB.current.range) {
            case 0: // LC Range

              LDB.CurrentMax = 1000;
              LDB.CurrentMin = 60;
              break;

            case 1: // MC Range
              LDB.CurrentMax = 100;
              LDB.CurrentMin = 6.5;
              break;

            case 2:
              LDB.CurrentMax = 50;
              LDB.CurrentMin = 2;
              break;
          }
      }

      break;

    case 2: //CP Load

      LDB.CurrentMax = 200;
      LDB.CurrentMin = 0;
      
      break;

  }
}
